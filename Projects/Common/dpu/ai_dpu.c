/**
  ******************************************************************************
  * @file    ai_dpu.c
  * @author  MCD Application Team
  * @brief   This file is implementing ai processing functions that are making
  * 		 use of libraries generated by X-CUBE-AI
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "logging_levels.h"
#define LOG_LEVEL    LOG_DEBUG
#include "logging.h"

/* Standard includes. */
#include <string.h>
#include <stdio.h>

/* Kernel includes. */
#include "ai_dpu.h"

/* Private function prototypes -----------------------------------------------*/
static BaseType_t AiDPUCheckModel(AIProcCtx_t * pxCtx)
{
  assert_param(pxCtx != NULL);
  BaseType_t res = pdTRUE;
  const ai_buffer *p_buffer;

  if (pxCtx->net_exec_ctx->report.api_version.major != AI_DPU_X_CUBE_AI_API_MAJOR ||
      pxCtx->net_exec_ctx->report.api_version.minor != AI_DPU_X_CUBE_AI_API_MINOR ||
      pxCtx->net_exec_ctx->report.api_version.micro != AI_DPU_X_CUBE_AI_API_MICRO )
  {
    res = pdFALSE;
  }
  if (pxCtx->net_exec_ctx->report.n_inputs > AI_DPU_NB_MAX_INPUT )
  {
    res = pdFALSE;
  }
  if (pxCtx->net_exec_ctx->report.n_outputs > AI_DPU_NB_MAX_OUTPUT )
  {
    res = pdFALSE;
  }
  for (int i=0; i< pxCtx->net_exec_ctx->report.n_inputs ; i++ )
  {
    p_buffer = &pxCtx->net_exec_ctx->report.inputs[i];
    if (AI_BUFFER_SHAPE_SIZE(p_buffer)                   != AI_DPU_SHAPE_SIZE        ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_BATCH)   >  AI_DPU_SHAPE_BATCH_MAX   ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_HEIGHT)  >  AI_DPU_SHAPE_HEIGHT_MAX  ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_WIDTH)   >  AI_DPU_SHAPE_WIDTH_MAX   ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_CHANNEL) >  AI_DPU_SHAPE_CHANNEL_MAX ||
        (AI_BUFFER_FMT_GET_TYPE(p_buffer->format)        != AI_BUFFER_FMT_TYPE_Q  &&
         AI_BUFFER_FMT_GET_TYPE(p_buffer->format)        != AI_BUFFER_FMT_TYPE_FLOAT))
    {
      res = pdFALSE;
    }
  }
  for (int i=0; i< pxCtx->net_exec_ctx->report.n_outputs ; i++ )
  {
    p_buffer = &pxCtx->net_exec_ctx->report.outputs[i];
    if (AI_BUFFER_SHAPE_SIZE(p_buffer)                   != AI_DPU_SHAPE_SIZE       ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_BATCH)   >  AI_DPU_SHAPE_BATCH_MAX  ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_HEIGHT)  >  AI_DPU_SHAPE_HEIGHT_MAX ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_WIDTH)   >  AI_DPU_SHAPE_WIDTH_MAX  ||
        AI_BUFFER_SHAPE_ELEM(p_buffer, AI_SHAPE_CHANNEL) >  AI_DPU_SHAPE_CHANNEL_MAX||
        AI_BUFFER_FMT_GET_TYPE(p_buffer->format)         != AI_BUFFER_FMT_TYPE_FLOAT)
    {
      res = pdFALSE;
    }
  }

  if (res == pdFALSE)
  {
    LogWarn("AI_DPU: Model check failed \r\n");
  }

  return res;
}

/* External functions --------------------------------------------------------*/
BaseType_t  AiDPULoadModel(AIProcCtx_t * pxCtx, const char *name)
{
  assert_param(pxCtx != NULL);
  (void) name;
  ai_error err;
  ai_handle activation_buffers[] = { pxCtx->activation_buffer};
  ai_buffer input;

  /* Create and initialize an instance of the model */
  err = ai_network_create_and_init(&pxCtx->net_exec_ctx->handle, activation_buffers, NULL);
  if (err.type != AI_ERROR_NONE) {
    aiLogErr(err, "ai_network_create_and_init");
    return pdFALSE;
  }

  ai_network_get_report(pxCtx->net_exec_ctx->handle, &pxCtx->net_exec_ctx->report);

  AiDPUCheckModel(pxCtx);

  /* allocate input or outputs in case not allocated by the model */
  aiPrintNetworkInfo(&pxCtx->net_exec_ctx->report);
  input = pxCtx->net_exec_ctx->report.inputs[0];

  /* init input data streams  */
  if ((pxCtx->net_exec_ctx->report.n_inputs == 1) \
      && (AI_BUFFER_FMT_GET_TYPE(input.format)==AI_BUFFER_FMT_TYPE_Q))
  {
    if (AI_BUFFER_FMT_TYPE_Q != AI_BUFFER_FMT_GET_TYPE(input.format) &&\
      ! AI_BUFFER_FMT_GET_SIGN(input.format) &&\
      8 != AI_BUFFER_FMT_GET_BITS(input.format))
    {
        LogError("expected signed integer 8 bits");
        return pdFALSE;
    }
    if (AI_BUFFER_META_INFO_INTQ(input.meta_info)) {
        float scale = AI_BUFFER_META_INFO_INTQ_GET_SCALE(input.meta_info, 0);
        if ( scale !=0 ){
        	pxCtx->input_Q_inv_scale =  1 / scale ;
        	pxCtx->input_Q_offset = (int8_t)AI_BUFFER_META_INFO_INTQ_GET_ZEROPOINT(input.meta_info, 0);
        }
    }
    else {
    	LogDebug("no meta info");
      return pdFALSE;
    }
  }
  return pdTRUE;
}

BaseType_t AiDPUReleaseModel(AIProcCtx_t * pxCtx)
{
  assert_param(pxCtx != NULL);
  if (pxCtx->net_exec_ctx->handle != AI_HANDLE_NULL) {
    if (ai_network_destroy(pxCtx->net_exec_ctx->handle) != AI_HANDLE_NULL ){
      ai_error err;
      err = ai_network_get_error(pxCtx->net_exec_ctx->handle);
      aiLogErr(err, "ai_network_destroy");
    }
    pxCtx->net_exec_ctx->handle = AI_HANDLE_NULL;
  }
  return pdTRUE;
}

BaseType_t AiDPUProcess(AIProcCtx_t *pxCtx, int8_t *p_spectro , float *pf_out)
{
  assert_param(_this != NULL);

  ai_i32 batch;
  ai_u16 n_outputs;
  ai_buffer* ai_input  = ai_network_inputs_get(pxCtx->net_exec_ctx->handle, NULL);
  ai_buffer* ai_output = ai_network_outputs_get(pxCtx->net_exec_ctx->handle, &n_outputs);

#ifndef AI_NETWORK_INPUTS_IN_ACTIVATIONS
  ai_input->data = AI_HANDLE_PTR(pxCtx->in);
#endif

#ifndef AI_NETWORK_OUTPUTS_IN_ACTIVATIONS
  ai_output[0].data = AI_HANDLE_PTR(pxCtx->out1);
#if (AI_NETWORK_OUT_NUM==2)
  if (n_outputs==2){
    ai_output[1].data = AI_HANDLE_PTR(pxCtx->out2);
  }
#endif
#endif

  ai_input[0].data = (ai_handle) p_spectro;
  ai_output[0].data = (ai_handle)pf_out;

  /* call Ai library. */
  batch = ai_network_run(pxCtx->net_exec_ctx->handle, ai_input, ai_output);

  /* prepare output */
  if (batch != 1) aiLogErr(ai_network_get_error(pxCtx->net_exec_ctx->handle),"ai_network_run");

  return pdTRUE;
}

