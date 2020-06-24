..
  Copyright 2019-2020 Intel Corporation

.. |any| replace:: :any:`any <dnnl::memory::format_tag::any>`
.. |abcdef| replace:: :any:`abcdef <dnnl::memory::format_tag::abcdef>`
.. |abcde| replace:: :any:`abcde <dnnl::memory::format_tag::abcde>`
.. |abcd| replace:: :any:`abcd <dnnl::memory::format_tag::abcd>`
.. |abc| replace:: :any:`abc <dnnl::memory::format_tag::abc>`
.. |ab| replace:: :any:`ab <dnnl::memory::format_tag::ab>`
.. |acb| replace:: :any:`acb <dnnl::memory::format_tag::acb>`
.. |acdb| replace:: :any:`acdb <dnnl::memory::format_tag::acdb>`
.. |acdeb| replace:: :any:`acdeb <dnnl::memory::format_tag::acdeb>`
.. |a| replace:: :any:`a <dnnl::memory::format_tag::a>`
.. |bac| replace:: :any:`bac <dnnl::memory::format_tag::bac>`
.. |ba| replace:: :any:`ba <dnnl::memory::format_tag::ba>`
.. |cba| replace:: :any:`cba <dnnl::memory::format_tag::cba>`
.. |cdba| replace:: :any:`cdba <dnnl::memory::format_tag::cdba>`
.. |cdeba| replace:: :any:`cdeba <dnnl::memory::format_tag::cdeba>`
.. |decab| replace:: :any:`decab <dnnl::memory::format_tag::decab>`
.. |dhwio| replace:: :any:`dhwio <dnnl::memory::format_tag::dhwio>`
.. |goidhw| replace:: :any:`goidhw <dnnl::memory::format_tag::goidhw>`
.. |goihw| replace:: :any:`goihw <dnnl::memory::format_tag::goihw>`
.. |goiw| replace:: :any:`goiw <dnnl::memory::format_tag::goiw>`
.. |hwigo| replace:: :any:`hwigo <dnnl::memory::format_tag::hwigo>`
.. |hwio| replace:: :any:`hwio <dnnl::memory::format_tag::hwio>`
.. |io| replace:: :any:`io <dnnl::memory::format_tag::io>`
.. |ldgoi| replace:: :any:`ldgoi <dnnl::memory::format_tag::ldgoi>`
.. |ldgo| replace:: :any:`ldgo <dnnl::memory::format_tag::ldgo>`
.. |ldigo| replace:: :any:`ldigo <dnnl::memory::format_tag::ldigo>`
.. |ldio| replace:: :any:`ldio <dnnl::memory::format_tag::ldio>`
.. |ldnc| replace:: :any:`ldnc <dnnl::memory::format_tag::ldnc>`
.. |ncdhw| replace:: :any:`ncdhw <dnnl::memory::format_tag::ncdhw>`
.. |nchw| replace:: :any:`nchw <dnnl::memory::format_tag::nchw>`
.. |ncw| replace:: :any:`ncw <dnnl::memory::format_tag::ncw>`
.. |nc| replace:: :any:`nc <dnnl::memory::format_tag::nc>`
.. |ndhwc| replace:: :any:`ndhwc <dnnl::memory::format_tag::ndhwc>`
.. |nhwc| replace:: :any:`nhwc <dnnl::memory::format_tag::nhwc>`
.. |ntc| replace:: :any:`ntc <dnnl::memory::format_tag::ntc>`
.. |nt| replace:: :any:`nt <dnnl::memory::format_tag::nt>`
.. |nwc| replace:: :any:`nwc <dnnl::memory::format_tag::nwc>`
.. |oidhw| replace:: :any:`oidhw <dnnl::memory::format_tag::oidhw>`
.. |oihw| replace:: :any:`oihw <dnnl::memory::format_tag::oihw>`
.. |oiw| replace:: :any:`oiw <dnnl::memory::format_tag::oiw>`
.. |oi| replace:: :any:`oi <dnnl::memory::format_tag::oi>`
.. |tnc| replace:: :any:`tnc <dnnl::memory::format_tag::tnc>`
.. |tn| replace:: :any:`tn <dnnl::memory::format_tag::tn>`
.. |wio| replace:: :any:`wio <dnnl::memory::format_tag::wio>`
.. |x| replace:: :any:`x <dnnl::memory::format_tag::x>`

.. |normalization_flags_none| replace:: :any:`none <dnnl::normalization_flags::none>`
.. |use_global_stats| replace:: :any:`use_global_stats <dnnl::normalization_flags::use_global_stats>`
.. |use_scaleshift| replace:: :any:`use_scaleshift <dnnl::normalization_flags::use_scaleshift>`
.. |fuse_norm_relu| replace:: :any:`fuse_norm_relu <dnnl::normalization_flags::fuse_norm_relu>`

.. |backward| replace:: :any:`backward <dnnl::prop_kind::backward>`
.. |backward_data| replace:: :any:`backward_data <dnnl::prop_kind::backward_data>`
.. |forward_inference| replace:: :any:`forward_inference <dnnl::prop_kind::forward_inference>`
.. |forward_training| replace:: :any:`forward_training <dnnl::prop_kind::forward_training>`

.. |binary_add| replace:: :any:`binary_add <dnnl::algorithm::binary_add>`
.. |binary_max| replace:: :any:`binary_max <dnnl::algorithm::binary_max>`
.. |binary_min| replace:: :any:`binary_min <dnnl::algorithm::binary_min>`
.. |binary_mul| replace:: :any:`binary_mul <dnnl::algorithm::binary_mul>`
.. |convolution_auto| replace:: :any:`convolution_auto <dnnl::algorithm::convolution_auto>`
.. |convolution_direct| replace:: :any:`convolution_direct <dnnl::algorithm::convolution_direct>`
.. |convolution_winograd| replace:: :any:`convolution_winograd <dnnl::algorithm::convolution_winograd>`
.. |deconvolution_direct| replace:: :any:`deconvolution_direct <dnnl::algorithm::deconvolution_direct>`
.. |deconvolution_winograd| replace:: :any:`deconvolution_winograd <dnnl::algorithm::deconvolution_winograd>`
.. |eltwise_abs| replace:: :any:`eltwise_abs <dnnl::algorithm::eltwise_abs>`
.. |eltwise_bounded_relu| replace:: :any:`eltwise_bounded_relu <dnnl::algorithm::eltwise_bounded_relu>`
.. |eltwise_clip| replace:: :any:`eltwise_clip <dnnl::algorithm::eltwise_clip>`
.. |eltwise_elu_use_dst_for_bwd| replace:: :any:`eltwise_elu_use_dst_for_bwd <dnnl::algorithm::eltwise_elu_use_dst_for_bwd>`
.. |eltwise_elu| replace:: :any:`eltwise_elu <dnnl::algorithm::eltwise_elu>`
.. |eltwise_exp_use_dst_for_bwd| replace:: :any:`eltwise_exp_use_dst_for_bwd <dnnl::algorithm::eltwise_exp_use_dst_for_bwd>`
.. |eltwise_exp| replace:: :any:`eltwise_exp <dnnl::algorithm::eltwise_exp>`
.. |eltwise_gelu_erf| replace:: :any:`eltwise_gelu_erf <dnnl::algorithm::eltwise_gelu_erf>`
.. |eltwise_gelu_tanh| replace:: :any:`eltwise_gelu_tanh <dnnl::algorithm::eltwise_gelu_tanh>`
.. |eltwise_gelu| replace:: :any:`eltwise_gelu <dnnl::algorithm::eltwise_gelu>`
.. |eltwise_linear| replace:: :any:`eltwise_linear <dnnl::algorithm::eltwise_linear>`
.. |eltwise_logistic_use_dst_for_bwd| replace:: :any:`eltwise_logistic_use_dst_for_bwd <dnnl::algorithm::eltwise_logistic_use_dst_for_bwd>`
.. |eltwise_logistic| replace:: :any:`eltwise_logistic <dnnl::algorithm::eltwise_logistic>`
.. |eltwise_log| replace:: :any:`eltwise_log <dnnl::algorithm::eltwise_log>`
.. |eltwise_pow| replace:: :any:`eltwise_pow <dnnl::algorithm::eltwise_pow>`
.. |eltwise_relu_use_dst_for_bwd| replace:: :any:`eltwise_relu_use_dst_for_bwd <dnnl::algorithm::eltwise_relu_use_dst_for_bwd>`
.. |eltwise_relu| replace:: :any:`eltwise_relu <dnnl::algorithm::eltwise_relu>`
.. |eltwise_soft_relu| replace:: :any:`eltwise_soft_relu <dnnl::algorithm::eltwise_soft_relu>`
.. |eltwise_sqrt_use_dst_for_bwd| replace:: :any:`eltwise_sqrt_use_dst_for_bwd <dnnl::algorithm::eltwise_sqrt_use_dst_for_bwd>`
.. |eltwise_sqrt| replace:: :any:`eltwise_sqrt <dnnl::algorithm::eltwise_sqrt>`
.. |eltwise_square| replace:: :any:`eltwise_square <dnnl::algorithm::eltwise_square>`
.. |eltwise_swish| replace:: :any:`eltwise_swish <dnnl::algorithm::eltwise_swish>`
.. |eltwise_tanh_use_dst_for_bwd| replace:: :any:`eltwise_tanh_use_dst_for_bwd <dnnl::algorithm::eltwise_tanh_use_dst_for_bwd>`
.. |eltwise_tanh| replace:: :any:`eltwise_tanh <dnnl::algorithm::eltwise_tanh>`
.. |lbr_gru| replace:: :any:`lbr_gru <dnnl::algorithm::lbr_gru>`
.. |lrn_across_channels| replace:: :any:`lrn_across_channels <dnnl::algorithm::lrn_across_channels>`
.. |lrn_within_channel| replace:: :any:`lrn_within_channel <dnnl::algorithm::lrn_within_channel>`
.. |pooling_avg_exclude_padding| replace:: :any:`pooling_avg_exclude_padding <dnnl::algorithm::pooling_avg_exclude_padding>`
.. |pooling_avg_include_padding| replace:: :any:`pooling_avg_include_padding <dnnl::algorithm::pooling_avg_include_padding>`
.. |pooling_avg| replace:: :any:`pooling_avg <dnnl::algorithm::pooling_avg>`
.. |pooling_max| replace:: :any:`pooling_max <dnnl::algorithm::pooling_max>`
.. |resampling_linear| replace:: :any:`resampling_linear <dnnl::algorithm::resampling_linear>`
.. |resampling_nearest| replace:: :any:`resampling_nearest <dnnl::algorithm::resampling_nearest>`
.. |undef| replace:: :any:`undef <dnnl::algorithm::undef>`
.. |vanilla_gru| replace:: :any:`vanilla_gru <dnnl::algorithm::vanilla_gru>`
.. |vanilla_lstm| replace:: :any:`vanilla_lstm <dnnl::algorithm::vanilla_lstm>`
.. |vanilla_rnn| replace:: :any:`vanilla_rnn <dnnl::algorithm::vanilla_rnn>`

.. |DNNL_ARG_SRC_0| replace:: :c:macro:`DNNL_ARG_SRC_0`
.. |DNNL_ARG_SRC| replace:: :c:macro:`DNNL_ARG_SRC`
.. |DNNL_ARG_SRC_LAYER| replace:: :c:macro:`DNNL_ARG_SRC_LAYER`
.. |DNNL_ARG_FROM| replace:: :c:macro:`DNNL_ARG_FROM`
.. |DNNL_ARG_SRC_1| replace:: :c:macro:`DNNL_ARG_SRC_1`
.. |DNNL_ARG_SRC_ITER| replace:: :c:macro:`DNNL_ARG_SRC_ITER`
.. |DNNL_ARG_SRC_2| replace:: :c:macro:`DNNL_ARG_SRC_2`
.. |DNNL_ARG_SRC_ITER_C| replace:: :c:macro:`DNNL_ARG_SRC_ITER_C`
.. |DNNL_ARG_DST_0| replace:: :c:macro:`DNNL_ARG_DST_0`
.. |DNNL_ARG_DST| replace:: :c:macro:`DNNL_ARG_DST`
.. |DNNL_ARG_TO| replace:: :c:macro:`DNNL_ARG_TO`
.. |DNNL_ARG_DST_LAYER| replace:: :c:macro:`DNNL_ARG_DST_LAYER`
.. |DNNL_ARG_DST_1| replace:: :c:macro:`DNNL_ARG_DST_1`
.. |DNNL_ARG_DST_ITER| replace:: :c:macro:`DNNL_ARG_DST_ITER`
.. |DNNL_ARG_DST_2| replace:: :c:macro:`DNNL_ARG_DST_2`
.. |DNNL_ARG_DST_ITER_C| replace:: :c:macro:`DNNL_ARG_DST_ITER_C`
.. |DNNL_ARG_WEIGHTS_0| replace:: :c:macro:`DNNL_ARG_WEIGHTS_0`
.. |DNNL_ARG_WEIGHTS| replace:: :c:macro:`DNNL_ARG_WEIGHTS`
.. |DNNL_ARG_SCALE_SHIFT| replace:: :c:macro:`DNNL_ARG_SCALE_SHIFT`
.. |DNNL_ARG_WEIGHTS_LAYER| replace:: :c:macro:`DNNL_ARG_WEIGHTS_LAYER`
.. |DNNL_ARG_WEIGHTS_1| replace:: :c:macro:`DNNL_ARG_WEIGHTS_1`
.. |DNNL_ARG_WEIGHTS_ITER| replace:: :c:macro:`DNNL_ARG_WEIGHTS_ITER`
.. |DNNL_ARG_BIAS| replace:: :c:macro:`DNNL_ARG_BIAS`
.. |DNNL_ARG_MEAN| replace:: :c:macro:`DNNL_ARG_MEAN`
.. |DNNL_ARG_VARIANCE| replace:: :c:macro:`DNNL_ARG_VARIANCE`
.. |DNNL_ARG_WORKSPACE| replace:: :c:macro:`DNNL_ARG_WORKSPACE`
.. |DNNL_ARG_SCRATCHPAD| replace:: :c:macro:`DNNL_ARG_SCRATCHPAD`
.. |DNNL_ARG_DIFF_SRC_0| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_0`
.. |DNNL_ARG_DIFF_SRC| replace:: :c:macro:`DNNL_ARG_DIFF_SRC`
.. |DNNL_ARG_DIFF_SRC_LAYER| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_LAYER`
.. |DNNL_ARG_DIFF_SRC_1| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_1`
.. |DNNL_ARG_DIFF_SRC_ITER| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_ITER`
.. |DNNL_ARG_DIFF_SRC_2| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_2`
.. |DNNL_ARG_DIFF_SRC_ITER_C| replace:: :c:macro:`DNNL_ARG_DIFF_SRC_ITER_C`
.. |DNNL_ARG_DIFF_DST_0| replace:: :c:macro:`DNNL_ARG_DIFF_DST_0`
.. |DNNL_ARG_DIFF_DST| replace:: :c:macro:`DNNL_ARG_DIFF_DST`
.. |DNNL_ARG_DIFF_DST_LAYER| replace:: :c:macro:`DNNL_ARG_DIFF_DST_LAYER`
.. |DNNL_ARG_DIFF_DST_1| replace:: :c:macro:`DNNL_ARG_DIFF_DST_1`
.. |DNNL_ARG_DIFF_DST_ITER| replace:: :c:macro:`DNNL_ARG_DIFF_DST_ITER`
.. |DNNL_ARG_DIFF_DST_2| replace:: :c:macro:`DNNL_ARG_DIFF_DST_2`
.. |DNNL_ARG_DIFF_DST_ITER_C| replace:: :c:macro:`DNNL_ARG_DIFF_DST_ITER_C`
.. |DNNL_ARG_DIFF_WEIGHTS_0| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_0`
.. |DNNL_ARG_DIFF_WEIGHTS| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS`
.. |DNNL_ARG_DIFF_SCALE_SHIFT| replace:: :c:macro:`DNNL_ARG_DIFF_SCALE_SHIFT`
.. |DNNL_ARG_DIFF_WEIGHTS_LAYER| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_LAYER`
.. |DNNL_ARG_DIFF_WEIGHTS_1| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_1`
.. |DNNL_ARG_DIFF_WEIGHTS_ITER| replace:: :c:macro:`DNNL_ARG_DIFF_WEIGHTS_ITER`
.. |DNNL_ARG_DIFF_BIAS| replace:: :c:macro:`DNNL_ARG_DIFF_BIAS`
.. |DNNL_ARG_ATTR_OUTPUT_SCALES| replace:: :c:macro:`DNNL_ARG_ATTR_OUTPUT_SCALES`
.. |DNNL_ARG_MULTIPLE_SRC| replace:: :c:macro:`DNNL_ARG_MULTIPLE_SRC`
.. |DNNL_ARG_MULTIPLE_DST| replace:: :c:macro:`DNNL_ARG_MULTIPLE_DST`
.. |DNNL_ARG_ATTR_ZERO_POINTS| replace:: :c:macro:`DNNL_ARG_ATTR_ZERO_POINTS`
.. |DNNL_RUNTIME_DIM_VAL| replace:: :c:macro:`DNNL_RUNTIME_DIM_VAL`
.. |DNNL_RUNTIME_SIZE_VAL| replace:: :c:macro:`DNNL_RUNTIME_SIZE_VAL`
.. |DNNL_RUNTIME_F32_VAL| replace:: :c:macro:`DNNL_RUNTIME_F32_VAL`
.. |DNNL_RUNTIME_S32_VAL| replace:: :c:macro:`DNNL_RUNTIME_S32_VAL`

