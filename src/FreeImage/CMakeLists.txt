project(FreeImage)

include( CheckIncludeFiles )
include( CheckStructHasMember )
include( CheckSymbolExists )

set(FREEIMAGERE_MAJOR_VERSION "0")
set(FREEIMAGERE_MINOR_VERSION "2")

set(FreeImage_SOURCES
	Source/CacheFile.h
	Source/FreeImage.h
	Source/FreeImage/BitmapAccess.cpp
	Source/FreeImage/CacheFile.cpp
	Source/FreeImage/ColorLookup.cpp
	Source/FreeImage.hpp
	Source/FreeImage/ConversionColor.cpp
	Source/FreeImage/ConversionYUV.cpp
	Source/FreeImage/ConversionYUV.h
	Source/FreeImage/SimpleTools.cpp
	Source/FreeImage/SimpleTools.h
	Source/FreeImage/tmoClamp.cpp
	Source/FreeImage/tmoLinear.cpp
	Source/FreeImage/Conversion.cpp
	Source/FreeImage/Conversion16_555.cpp
	Source/FreeImage/Conversion16_565.cpp
	Source/FreeImage/Conversion24.cpp
	Source/FreeImage/Conversion32.cpp
    Source/FreeImage/ConversionFloat.cpp
    Source/FreeImage/ConversionRGB16.cpp
	Source/FreeImage/ConversionRGBA16.cpp
	Source/FreeImage/ConversionRGBAF.cpp
	Source/FreeImage/Conversion4.cpp
	Source/FreeImage/Conversion8.cpp
	Source/FreeImage/ConversionRGBF.cpp
	Source/FreeImage/ConversionType.cpp
    Source/FreeImage/ConversionUINT16.cpp
	Source/FreeImage/FreeImage.cpp
	Source/FreeImage/FreeImageIO.cpp
	Source/FreeImage/GetType.cpp
	Source/FreeImage/Halftoning.cpp
	Source/FreeImage/J2KHelper.cpp
	Source/FreeImage/J2KHelper.h
	Source/FreeImage/LFPQuantizer.cpp
	Source/FreeImage/MemoryIO.cpp
    Source/FreeImage/MNGHelper.cpp
	Source/FreeImage/MultiPage.cpp
	Source/FreeImage/NNQuantizer.cpp
	Source/FreeImage/PSDParser.cpp
	Source/FreeImage/PSDParser.h
	Source/FreeImage/PixelAccess.cpp
	Source/FreeImage/Plugin.cpp
	Source/FreeImage/PluginBMP.cpp
	Source/FreeImage/PluginCUT.cpp
	Source/FreeImage/PluginDDS.cpp
	Source/FreeImage/PluginEXR.cpp
	Source/FreeImage/PluginG3.cpp
	Source/FreeImage/PluginGIF.cpp
	Source/FreeImage/PluginHDR.cpp
	Source/FreeImage/PluginICO.cpp
	Source/FreeImage/PluginIFF.cpp
	Source/FreeImage/PluginJ2K.cpp
    Source/FreeImage/PluginJNG.cpp
	Source/FreeImage/PluginJP2.cpp
	Source/FreeImage/PluginJPEG.cpp
	Source/FreeImage/PluginJXR.cpp
	Source/FreeImage/PluginKOALA.cpp
	Source/FreeImage/PluginMNG.cpp
	Source/FreeImage/PluginPCD.cpp
	Source/FreeImage/PluginPCX.cpp
	Source/FreeImage/PluginPFM.cpp
	Source/FreeImage/PluginPICT.cpp
	Source/FreeImage/PluginPNG.cpp
	Source/FreeImage/PluginPNM.cpp
	Source/FreeImage/PluginPSD.cpp
	Source/FreeImage/PluginRAS.cpp
	Source/FreeImage/PluginRAW.cpp
	Source/FreeImage/PluginSGI.cpp
	Source/FreeImage/PluginTARGA.cpp
	Source/FreeImage/PluginTIFF.cpp
	Source/FreeImage/PluginWBMP.cpp
	Source/FreeImage/PluginWebP.cpp
	Source/FreeImage/PluginXBM.cpp
	Source/FreeImage/PluginXPM.cpp
	Source/FreeImage/TIFFLogLuv.cpp
	Source/FreeImage/ToneMapping.cpp
	Source/FreeImage/WuQuantizer.cpp
	Source/FreeImage/ZLibInterface.cpp
	Source/FreeImage/tmoColorConvert.cpp
	Source/FreeImage/tmoDrago03.cpp
	Source/FreeImage/tmoFattal02.cpp
	Source/FreeImage/tmoReinhard05.cpp
	Source/FreeImageIO.h
	Source/FreeImageToolkit/BSplineRotate.cpp
	Source/FreeImageToolkit/Background.cpp
	Source/FreeImageToolkit/Channels.cpp
	Source/FreeImageToolkit/ClassicRotate.cpp
	Source/FreeImageToolkit/Colors.cpp
	Source/FreeImageToolkit/CopyPaste.cpp
	Source/FreeImageToolkit/Display.cpp
	Source/FreeImageToolkit/Filters.h
	Source/FreeImageToolkit/Flip.cpp
	Source/FreeImageToolkit/JPEGTransform.cpp
	Source/FreeImageToolkit/MultigridPoissonSolver.cpp
	Source/FreeImageToolkit/Rescale.cpp
	Source/FreeImageToolkit/Resize.cpp
	Source/FreeImageToolkit/Resize.h
	Source/LibJPEG/jaricom.c
	Source/LibJPEG/jcapimin.c
	Source/LibJPEG/jcapistd.c
	Source/LibJPEG/jcarith.c
	Source/LibJPEG/jccoefct.c
	Source/LibJPEG/jccolor.c
	Source/LibJPEG/jcdctmgr.c
	Source/LibJPEG/jchuff.c
	Source/LibJPEG/jcinit.c
	Source/LibJPEG/jcmainct.c
	Source/LibJPEG/jcmarker.c
	Source/LibJPEG/jcmaster.c
	Source/LibJPEG/jcomapi.c
	Source/LibJPEG/jconfig.h
	Source/LibJPEG/jcparam.c
	Source/LibJPEG/jcprepct.c
	Source/LibJPEG/jcsample.c
	Source/LibJPEG/jctrans.c
	Source/LibJPEG/jdapimin.c
	Source/LibJPEG/jdapistd.c
	Source/LibJPEG/jdarith.c
	Source/LibJPEG/jdatadst.c
	Source/LibJPEG/jdatasrc.c
	Source/LibJPEG/jdcoefct.c
	Source/LibJPEG/jdcolor.c
	Source/LibJPEG/jdct.h
	Source/LibJPEG/jddctmgr.c
	Source/LibJPEG/jdhuff.c
	Source/LibJPEG/jdinput.c
	Source/LibJPEG/jdmainct.c
	Source/LibJPEG/jdmarker.c
	Source/LibJPEG/jdmaster.c
	Source/LibJPEG/jdmerge.c
	Source/LibJPEG/jdpostct.c
	Source/LibJPEG/jdsample.c
	Source/LibJPEG/jdtrans.c
	Source/LibJPEG/jerror.c
	Source/LibJPEG/jerror.h
	Source/LibJPEG/jfdctflt.c
	Source/LibJPEG/jfdctfst.c
	Source/LibJPEG/jfdctint.c
	Source/LibJPEG/jidctflt.c
	Source/LibJPEG/jidctfst.c
	Source/LibJPEG/jidctint.c
	Source/LibJPEG/jinclude.h
	Source/LibJPEG/jmemmgr.c
	Source/LibJPEG/jmemnobs.c
	Source/LibJPEG/jmemsys.h
	Source/LibJPEG/jmorecfg.h
	Source/LibJPEG/jpegint.h
	Source/LibJPEG/jpeglib.h
	Source/LibJPEG/jquant1.c
	Source/LibJPEG/jquant2.c
	Source/LibJPEG/jutils.c
	Source/LibJPEG/jversion.h
	Source/LibJPEG/transupp.c
	Source/LibJPEG/transupp.h
	Source/LibJXR/image/decode/decode.c
	Source/LibJXR/image/decode/JXRTranscode.c
	Source/LibJXR/image/decode/postprocess.c
	Source/LibJXR/image/decode/segdec.c
	Source/LibJXR/image/decode/strdec.c
	Source/LibJXR/image/decode/strdec_x86.c
	Source/LibJXR/image/decode/strInvTransform.c
	Source/LibJXR/image/decode/strPredQuantDec.c
	Source/LibJXR/image/encode/encode.c
	Source/LibJXR/image/encode/segenc.c
	Source/LibJXR/image/encode/strenc.c
	Source/LibJXR/image/encode/strenc_x86.c
	Source/LibJXR/image/encode/strFwdTransform.c
	Source/LibJXR/image/encode/strPredQuantEnc.c
	Source/LibJXR/image/sys/adapthuff.c
	Source/LibJXR/image/sys/image.c
	Source/LibJXR/image/sys/strcodec.c
	Source/LibJXR/image/sys/strPredQuant.c
	Source/LibJXR/image/sys/strTransform.c
	Source/LibJXR/jxrgluelib/JXRGlue.c
	Source/LibJXR/jxrgluelib/JXRGlueJxr.c
	Source/LibJXR/jxrgluelib/JXRGluePFC.c
	Source/LibJXR/jxrgluelib/JXRMeta.c
	Source/openjp2/bio.c
	Source/openjp2/bio.h
	# Source/openjp2/cidx_manager.c
	# Source/openjp2/cidx_manager.h
	Source/openjp2/cio.c
	Source/openjp2/cio.h
	Source/openjp2/dwt.c
	Source/openjp2/dwt.h
	Source/openjp2/event.c
	Source/openjp2/event.h
	Source/openjp2/function_list.c
	Source/openjp2/function_list.h
	Source/openjp2/ht_dec.c
	Source/openjp2/image.c
	Source/openjp2/image.h
	Source/openjp2/invert.c
	Source/openjp2/indexbox_manager.h
	Source/openjp2/j2k.c
	Source/openjp2/j2k.h
	Source/openjp2/jp2.c
	Source/openjp2/jp2.h
	Source/openjp2/mct.c
	Source/openjp2/mct.h
	Source/openjp2/mqc.c
	Source/openjp2/mqc.h
	Source/openjp2/openjpeg.c
	Source/openjp2/openjpeg.h
	Source/openjp2/opj_config.h
	Source/openjp2/opj_includes.h
	Source/openjp2/opj_malloc.c
	Source/openjp2/opj_malloc.h
	# Source/openjp2/phix_manager.c
	Source/openjp2/pi.c
	Source/openjp2/pi.h
	# Source/openjp2/ppix_manager.c
	Source/openjp2/sparse_array.c
	Source/openjp2/t1.c
	Source/openjp2/t1.h
	Source/openjp2/t1_luts.h
	Source/openjp2/t2.c
	Source/openjp2/t2.h
	Source/openjp2/tcd.c
	Source/openjp2/tcd.h
	Source/openjp2/tgt.c
	Source/openjp2/tgt.h
	Source/openjp2/thread.c
	# Source/openjp2/thix_manager.c
	# Source/openjp2/tpix_manager.c
	Source/LibPNG/png.c
	Source/LibPNG/png.h
	Source/LibPNG/pngconf.h
    Source/LibPNG/pngdebug.h
	Source/LibPNG/pngerror.c
	Source/LibPNG/pngget.c
    Source/LibPNG/pnginfo.h
    Source/LibPNG/pnglibconf.h
	Source/LibPNG/pngmem.c
	Source/LibPNG/pngpread.c
	Source/LibPNG/pngread.c
    Source/LibPNG/pngpriv.h
	Source/LibPNG/pngrio.c
	Source/LibPNG/pngrtran.c
	Source/LibPNG/pngrutil.c
	Source/LibPNG/pngset.c
    Source/LibPNG/pngstruct.h
	Source/LibPNG/pngtrans.c
	Source/LibPNG/pngwio.c
	Source/LibPNG/pngwrite.c
	Source/LibPNG/pngwtran.c
	Source/LibPNG/pngwutil.c
	Source/LibRawLite/internal/dcraw_common.cpp
	Source/LibRawLite/internal/dcraw_fileio.cpp
	Source/LibRawLite/internal/defines.h
	Source/LibRawLite/internal/demosaic_packs.cpp
	Source/LibRawLite/internal/libraw_internal_funcs.h
	Source/LibRawLite/internal/var_defines.h
	Source/LibRawLite/libraw/libraw.h
	Source/LibRawLite/libraw/libraw_alloc.h
	Source/LibRawLite/libraw/libraw_const.h
	Source/LibRawLite/libraw/libraw_datastream.h
	Source/LibRawLite/libraw/libraw_internal.h
	Source/LibRawLite/libraw/libraw_types.h
	Source/LibRawLite/libraw/libraw_version.h
	Source/LibRawLite/src/libraw_c_api.cpp
	Source/LibRawLite/src/libraw_cxx.cpp
    Source/LibRawLite/src/libraw_datastream.cpp
	Source/LibTIFF4/t4.h
	Source/LibTIFF4/tif_aux.c
	Source/LibTIFF4/tif_close.c
	Source/LibTIFF4/tif_codec.c
	Source/LibTIFF4/tif_color.c
	Source/LibTIFF4/tif_compress.c
	Source/LibTIFF4/tif_config.h
	Source/LibTIFF4/tif_dir.c
	Source/LibTIFF4/tif_dir.h
	Source/LibTIFF4/tif_dirinfo.c
	Source/LibTIFF4/tif_dirread.c
	Source/LibTIFF4/tif_dirwrite.c
	Source/LibTIFF4/tif_dumpmode.c
	Source/LibTIFF4/tif_error.c
	Source/LibTIFF4/tif_extension.c
	Source/LibTIFF4/tif_fax3.c
	Source/LibTIFF4/tif_fax3.h
	Source/LibTIFF4/tif_fax3sm.c
	Source/LibTIFF4/tif_flush.c
	Source/LibTIFF4/tif_getimage.c
	Source/LibTIFF4/tif_jpeg.c
    Source/LibTIFF4/tif_jpeg_12.c
    Source/LibTIFF4/tif_lerc.c
	Source/LibTIFF4/tif_luv.c
    Source/LibTIFF4/tif_lzma.c
	Source/LibTIFF4/tif_lzw.c
	Source/LibTIFF4/tif_next.c
	Source/LibTIFF4/tif_ojpeg.c
	Source/LibTIFF4/tif_open.c
	Source/LibTIFF4/tif_packbits.c
	Source/LibTIFF4/tif_pixarlog.c
	Source/LibTIFF4/tif_predict.c
	Source/LibTIFF4/tif_predict.h
	Source/LibTIFF4/tif_print.c
	Source/LibTIFF4/tif_read.c
	Source/LibTIFF4/tif_strip.c
	Source/LibTIFF4/tif_swab.c
	Source/LibTIFF4/tif_thunder.c
	Source/LibTIFF4/tif_tile.c
	Source/LibTIFF4/tif_version.c
	Source/LibTIFF4/tif_warning.c
	Source/LibTIFF4/tif_webp.c
	Source/LibTIFF4/tif_write.c
	Source/LibTIFF4/tif_zip.c
	Source/LibTIFF4/tiff.h
	Source/LibTIFF4/tiffio.h
	Source/LibTIFF4/tiffiop.h
	Source/LibTIFF4/tiffvers.h
	Source/LibTIFF4/uvcode.h
	Source/LibWebP/sharpyuv/sharpyuv.c
	Source/LibWebP/sharpyuv/sharpyuv_csp.c
	Source/LibWebP/sharpyuv/sharpyuv_csp.h
	Source/LibWebP/sharpyuv/sharpyuv_dsp.c
	Source/LibWebP/sharpyuv/sharpyuv_dsp.h
	Source/LibWebP/sharpyuv/sharpyuv_gamma.c
	Source/LibWebP/sharpyuv/sharpyuv_gamma.h
	Source/LibWebP/sharpyuv/sharpyuv.h
	Source/LibWebP/sharpyuv/sharpyuv_neon.c
	Source/LibWebP/sharpyuv/sharpyuv_sse2.c
	Source/LibWebP/src/mux/muxinternal.c
	Source/LibWebP/src/mux/muxedit.c
	Source/LibWebP/src/mux/anim_encode.c
	Source/LibWebP/src/mux/muxread.c
	Source/LibWebP/src/mux/animi.h
	Source/LibWebP/src/mux/muxi.h
	Source/LibWebP/src/enc/histogram_enc.c
	Source/LibWebP/src/enc/picture_csp_enc.c
	Source/LibWebP/src/enc/webp_enc.c
	Source/LibWebP/src/enc/filter_enc.c
	Source/LibWebP/src/enc/backward_references_enc.c
	Source/LibWebP/src/enc/picture_rescale_enc.c
	Source/LibWebP/src/enc/iterator_enc.c
	Source/LibWebP/src/enc/config_enc.c
	Source/LibWebP/src/enc/picture_enc.c
	Source/LibWebP/src/enc/analysis_enc.c
	Source/LibWebP/src/enc/vp8i_enc.h
	Source/LibWebP/src/enc/near_lossless_enc.c
	Source/LibWebP/src/enc/quant_enc.c
	Source/LibWebP/src/enc/cost_enc.h
	Source/LibWebP/src/enc/alpha_enc.c
	Source/LibWebP/src/enc/histogram_enc.h
	Source/LibWebP/src/enc/picture_tools_enc.c
	Source/LibWebP/src/enc/frame_enc.c
	Source/LibWebP/src/enc/tree_enc.c
	Source/LibWebP/src/enc/vp8li_enc.h
	Source/LibWebP/src/enc/picture_psnr_enc.c
	Source/LibWebP/src/enc/predictor_enc.c
	Source/LibWebP/src/enc/syntax_enc.c
	Source/LibWebP/src/enc/vp8l_enc.c
	Source/LibWebP/src/enc/cost_enc.c
	Source/LibWebP/src/enc/backward_references_enc.h
	Source/LibWebP/src/enc/token_enc.c
	Source/LibWebP/src/enc/backward_references_cost_enc.c
	Source/LibWebP/src/utils/quant_levels_dec_utils.h
	Source/LibWebP/src/utils/random_utils.h
	Source/LibWebP/src/utils/thread_utils.h
	Source/LibWebP/src/utils/bit_writer_utils.h
	Source/LibWebP/src/utils/quant_levels_dec_utils.c
	Source/LibWebP/src/utils/quant_levels_utils.c
	Source/LibWebP/src/utils/huffman_utils.h
	Source/LibWebP/src/utils/bit_reader_inl_utils.h
	Source/LibWebP/src/utils/bit_reader_utils.h
	Source/LibWebP/src/utils/quant_levels_utils.h
	Source/LibWebP/src/utils/huffman_encode_utils.c
	Source/LibWebP/src/utils/endian_inl_utils.h
	Source/LibWebP/src/utils/color_cache_utils.h
	Source/LibWebP/src/utils/color_cache_utils.c
	Source/LibWebP/src/utils/huffman_encode_utils.h
	Source/LibWebP/src/utils/rescaler_utils.h
	Source/LibWebP/src/utils/filters_utils.c
	Source/LibWebP/src/utils/bit_reader_utils.c
	Source/LibWebP/src/utils/rescaler_utils.c
	Source/LibWebP/src/utils/huffman_utils.c
	Source/LibWebP/src/utils/random_utils.c
	Source/LibWebP/src/utils/thread_utils.c
	Source/LibWebP/src/utils/utils.h
	Source/LibWebP/src/utils/filters_utils.h
	Source/LibWebP/src/utils/utils.c
	Source/LibWebP/src/utils/bit_writer_utils.c
	Source/LibWebP/src/webp/decode.h
	Source/LibWebP/src/webp/mux_types.h
	Source/LibWebP/src/webp/demux.h
	Source/LibWebP/src/webp/mux.h
	Source/LibWebP/src/webp/format_constants.h
	Source/LibWebP/src/webp/types.h
	Source/LibWebP/src/webp/encode.h
	Source/LibWebP/src/dec/buffer_dec.c
	Source/LibWebP/src/dec/idec_dec.c
	Source/LibWebP/src/dec/vp8li_dec.h
	Source/LibWebP/src/dec/io_dec.c
	Source/LibWebP/src/dec/common_dec.h
	Source/LibWebP/src/dec/tree_dec.c
	Source/LibWebP/src/dec/webp_dec.c
	Source/LibWebP/src/dec/webpi_dec.h
	Source/LibWebP/src/dec/vp8_dec.c
	Source/LibWebP/src/dec/alphai_dec.h
	Source/LibWebP/src/dec/frame_dec.c
	Source/LibWebP/src/dec/quant_dec.c
	Source/LibWebP/src/dec/vp8i_dec.h
	Source/LibWebP/src/dec/alpha_dec.c
	Source/LibWebP/src/dec/vp8l_dec.c
	Source/LibWebP/src/dec/vp8_dec.h
	Source/LibWebP/src/demux/anim_decode.c
	Source/LibWebP/src/demux/demux.c
	Source/LibWebP/src/dsp/filters.c
	Source/LibWebP/src/dsp/lossless_sse2.c
	Source/LibWebP/src/dsp/lossless_sse41.c
	Source/LibWebP/src/dsp/enc_sse41.c
	Source/LibWebP/src/dsp/common_sse2.h
	Source/LibWebP/src/dsp/dec_mips_dsp_r2.c
	Source/LibWebP/src/dsp/alpha_processing_neon.c
	Source/LibWebP/src/dsp/filters_neon.c
	Source/LibWebP/src/dsp/yuv_neon.c
	Source/LibWebP/src/dsp/rescaler_neon.c
	Source/LibWebP/src/dsp/upsampling_mips_dsp_r2.c
	Source/LibWebP/src/dsp/filters_sse2.c
	Source/LibWebP/src/dsp/mips_macro.h
	Source/LibWebP/src/dsp/dsp.h
	Source/LibWebP/src/dsp/rescaler.c
	Source/LibWebP/src/dsp/rescaler_msa.c
	Source/LibWebP/src/dsp/cost_mips_dsp_r2.c
	Source/LibWebP/src/dsp/upsampling_neon.c
	Source/LibWebP/src/dsp/upsampling.c
	Source/LibWebP/src/dsp/ssim.c
	Source/LibWebP/src/dsp/neon.h
	Source/LibWebP/src/dsp/lossless_neon.c
	Source/LibWebP/src/dsp/enc_mips32.c
	Source/LibWebP/src/dsp/lossless_enc.c
	Source/LibWebP/src/dsp/rescaler_mips32.c
	Source/LibWebP/src/dsp/dec_sse2.c
	Source/LibWebP/src/dsp/lossless.c
	Source/LibWebP/src/dsp/yuv_mips_dsp_r2.c
	Source/LibWebP/src/dsp/yuv_sse41.c
	Source/LibWebP/src/dsp/dec_sse41.c
	Source/LibWebP/src/dsp/lossless.h
	Source/LibWebP/src/dsp/ssim_sse2.c
	Source/LibWebP/src/dsp/rescaler_mips_dsp_r2.c
	Source/LibWebP/src/dsp/lossless_common.h
	Source/LibWebP/src/dsp/dec_clip_tables.c
	Source/LibWebP/src/dsp/upsampling_msa.c
	Source/LibWebP/src/dsp/cost_neon.c
	Source/LibWebP/src/dsp/cost_sse2.c
	Source/LibWebP/src/dsp/msa_macro.h
	Source/LibWebP/src/dsp/enc_neon.c
	Source/LibWebP/src/dsp/upsampling_sse41.c
	Source/LibWebP/src/dsp/enc_msa.c
	Source/LibWebP/src/dsp/lossless_enc_mips32.c
	Source/LibWebP/src/dsp/alpha_processing.c
	Source/LibWebP/src/dsp/lossless_mips_dsp_r2.c
	Source/LibWebP/src/dsp/lossless_enc_sse2.c
	Source/LibWebP/src/dsp/cost_mips32.c
	Source/LibWebP/src/dsp/lossless_enc_msa.c
	Source/LibWebP/src/dsp/enc_sse2.c
	Source/LibWebP/src/dsp/enc_mips_dsp_r2.c
	Source/LibWebP/src/dsp/alpha_processing_sse41.c
	Source/LibWebP/src/dsp/dec.c
	Source/LibWebP/src/dsp/common_sse41.h
	Source/LibWebP/src/dsp/yuv_sse2.c
	Source/LibWebP/src/dsp/alpha_processing_sse2.c
	Source/LibWebP/src/dsp/lossless_enc_neon.c
	Source/LibWebP/src/dsp/dec_msa.c
	Source/LibWebP/src/dsp/alpha_processing_mips_dsp_r2.c
	Source/LibWebP/src/dsp/yuv_mips32.c
	Source/LibWebP/src/dsp/cpu.c
	Source/LibWebP/src/dsp/yuv.h
	Source/LibWebP/src/dsp/enc.c
	Source/LibWebP/src/dsp/cost.c
	Source/LibWebP/src/dsp/yuv.c
	Source/LibWebP/src/dsp/lossless_enc_mips_dsp_r2.c
	Source/LibWebP/src/dsp/dec_mips32.c
	Source/LibWebP/src/dsp/filters_mips_dsp_r2.c
	Source/LibWebP/src/dsp/dec_neon.c
	Source/LibWebP/src/dsp/lossless_msa.c
	Source/LibWebP/src/dsp/filters_msa.c
	Source/LibWebP/src/dsp/rescaler_sse2.c
	Source/LibWebP/src/dsp/upsampling_sse2.c
	Source/LibWebP/src/dsp/lossless_enc_sse41.c
	Source/Metadata/Exif.cpp
	Source/Metadata/FIRational.cpp
	Source/Metadata/FIRational.h
	Source/Metadata/FreeImageTag.cpp
	Source/Metadata/FreeImageTag.h
	Source/Metadata/IPTC.cpp
	Source/Metadata/TagConversion.cpp
	Source/Metadata/TagLib.cpp
	Source/Metadata/XTIFF.cpp
	Source/OpenEXR/Iex/IexBaseExc.cpp
	Source/OpenEXR/Iex/IexBaseExc.h
	Source/OpenEXR/Iex/IexErrnoExc.h
	Source/OpenEXR/Iex/IexExport.h
	Source/OpenEXR/Iex/IexForward.h
	Source/OpenEXR/Iex/Iex.h
	Source/OpenEXR/Iex/IexMacros.h
	Source/OpenEXR/Iex/IexMathExc.h
	Source/OpenEXR/Iex/IexMathFloatExc.cpp
	Source/OpenEXR/Iex/IexMathFloatExc.h
	Source/OpenEXR/Iex/IexMathFpu.cpp
	Source/OpenEXR/Iex/IexMathFpu.h
	Source/OpenEXR/Iex/IexMathIeeeExc.h
	Source/OpenEXR/Iex/IexNamespace.h
	Source/OpenEXR/Iex/IexThrowErrnoExc.cpp
	Source/OpenEXR/Iex/IexThrowErrnoExc.h
	Source/OpenEXR/IlmThread/IlmThread.cpp
	Source/OpenEXR/IlmThread/IlmThreadExport.h
	Source/OpenEXR/IlmThread/IlmThreadForward.h
	Source/OpenEXR/IlmThread/IlmThread.h
	Source/OpenEXR/IlmThread/IlmThreadMutex.h
	Source/OpenEXR/IlmThread/IlmThreadNamespace.h
	Source/OpenEXR/IlmThread/IlmThreadPool.cpp
	Source/OpenEXR/IlmThread/IlmThreadPool.h
	Source/OpenEXR/IlmThread/IlmThreadSemaphore.h
	Source/OpenEXR/Imath/half.cpp
	Source/OpenEXR/Imath/halfFunction.h
	Source/OpenEXR/Imath/half.h
	Source/OpenEXR/Imath/halfLimits.h
	Source/OpenEXR/Imath/ImathBoxAlgo.h
	Source/OpenEXR/Imath/ImathBox.h
	Source/OpenEXR/Imath/ImathColorAlgo.cpp
	Source/OpenEXR/Imath/ImathColorAlgo.h
	Source/OpenEXR/Imath/ImathColor.h
	Source/OpenEXR/Imath/ImathEuler.h
	Source/OpenEXR/Imath/ImathExport.h
	Source/OpenEXR/Imath/ImathForward.h
	Source/OpenEXR/Imath/ImathFrame.h
	Source/OpenEXR/Imath/ImathFrustum.h
	Source/OpenEXR/Imath/ImathFrustumTest.h
	Source/OpenEXR/Imath/ImathFun.cpp
	Source/OpenEXR/Imath/ImathFun.h
	Source/OpenEXR/Imath/ImathGL.h
	Source/OpenEXR/Imath/ImathGLU.h
	Source/OpenEXR/Imath/ImathInt64.h
	Source/OpenEXR/Imath/ImathInterval.h
	Source/OpenEXR/Imath/ImathLineAlgo.h
	Source/OpenEXR/Imath/ImathLine.h
	Source/OpenEXR/Imath/ImathMath.h
	Source/OpenEXR/Imath/ImathMatrixAlgo.cpp
	Source/OpenEXR/Imath/ImathMatrixAlgo.h
	Source/OpenEXR/Imath/ImathMatrix.h
	Source/OpenEXR/Imath/ImathNamespace.h
	Source/OpenEXR/Imath/ImathPlane.h
	Source/OpenEXR/Imath/ImathPlatform.h
	Source/OpenEXR/Imath/ImathQuat.h
	Source/OpenEXR/Imath/ImathRandom.cpp
	Source/OpenEXR/Imath/ImathRandom.h
	Source/OpenEXR/Imath/ImathRoots.h
	Source/OpenEXR/Imath/ImathShear.h
	Source/OpenEXR/Imath/ImathSphere.h
	Source/OpenEXR/Imath/ImathTypeTraits.h
	Source/OpenEXR/Imath/ImathVecAlgo.h
	Source/OpenEXR/Imath/ImathVec.h
	Source/OpenEXR/Imath/toFloat.cpp
	Source/OpenEXR/Imath/toFloat.h
	Source/OpenEXR/OpenEXR/b44ExpLogTable.cpp
	Source/OpenEXR/OpenEXR/b44ExpLogTable.h
	Source/OpenEXR/OpenEXR/dwaLookups.h
	Source/OpenEXR/OpenEXR/ImfAcesFile.cpp
	Source/OpenEXR/OpenEXR/ImfAcesFile.h
	Source/OpenEXR/OpenEXR/ImfArray.h
	Source/OpenEXR/OpenEXR/ImfAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfAttribute.h
	Source/OpenEXR/OpenEXR/ImfAutoArray.h
	Source/OpenEXR/OpenEXR/ImfB44Compressor.cpp
	Source/OpenEXR/OpenEXR/ImfB44Compressor.h
	Source/OpenEXR/OpenEXR/ImfBoxAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfBoxAttribute.h
	Source/OpenEXR/OpenEXR/ImfChannelListAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfChannelListAttribute.h
	Source/OpenEXR/OpenEXR/ImfChannelList.cpp
	Source/OpenEXR/OpenEXR/ImfChannelList.h
	Source/OpenEXR/OpenEXR/ImfCheckedArithmetic.h
	Source/OpenEXR/OpenEXR/ImfChromaticitiesAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfChromaticitiesAttribute.h
	Source/OpenEXR/OpenEXR/ImfChromaticities.cpp
	Source/OpenEXR/OpenEXR/ImfChromaticities.h
	Source/OpenEXR/OpenEXR/ImfCompositeDeepScanLine.cpp
	Source/OpenEXR/OpenEXR/ImfCompositeDeepScanLine.h
	Source/OpenEXR/OpenEXR/ImfCompressionAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfCompressionAttribute.h
	Source/OpenEXR/OpenEXR/ImfCompression.h
	Source/OpenEXR/OpenEXR/ImfCompressor.cpp
	Source/OpenEXR/OpenEXR/ImfCompressor.h
	Source/OpenEXR/OpenEXR/ImfConvert.cpp
	Source/OpenEXR/OpenEXR/ImfConvert.h
	Source/OpenEXR/OpenEXR/ImfCRgbaFile.cpp
	Source/OpenEXR/OpenEXR/ImfCRgbaFile.h
	Source/OpenEXR/OpenEXR/ImfDeepCompositing.cpp
	Source/OpenEXR/OpenEXR/ImfDeepCompositing.h
	Source/OpenEXR/OpenEXR/ImfDeepFrameBuffer.cpp
	Source/OpenEXR/OpenEXR/ImfDeepFrameBuffer.h
	Source/OpenEXR/OpenEXR/ImfDeepImageStateAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfDeepImageStateAttribute.h
	Source/OpenEXR/OpenEXR/ImfDeepImageState.h
	Source/OpenEXR/OpenEXR/ImfDeepScanLineInputFile.cpp
	Source/OpenEXR/OpenEXR/ImfDeepScanLineInputFile.h
	Source/OpenEXR/OpenEXR/ImfDeepScanLineInputPart.cpp
	Source/OpenEXR/OpenEXR/ImfDeepScanLineInputPart.h
	Source/OpenEXR/OpenEXR/ImfDeepScanLineOutputFile.cpp
	Source/OpenEXR/OpenEXR/ImfDeepScanLineOutputFile.h
	Source/OpenEXR/OpenEXR/ImfDeepScanLineOutputPart.cpp
	Source/OpenEXR/OpenEXR/ImfDeepScanLineOutputPart.h
	Source/OpenEXR/OpenEXR/ImfDeepTiledInputFile.cpp
	Source/OpenEXR/OpenEXR/ImfDeepTiledInputFile.h
	Source/OpenEXR/OpenEXR/ImfDeepTiledInputPart.cpp
	Source/OpenEXR/OpenEXR/ImfDeepTiledInputPart.h
	Source/OpenEXR/OpenEXR/ImfDeepTiledOutputFile.cpp
	Source/OpenEXR/OpenEXR/ImfDeepTiledOutputFile.h
	Source/OpenEXR/OpenEXR/ImfDeepTiledOutputPart.cpp
	Source/OpenEXR/OpenEXR/ImfDeepTiledOutputPart.h
	Source/OpenEXR/OpenEXR/ImfDoubleAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfDoubleAttribute.h
	Source/OpenEXR/OpenEXR/ImfDwaCompressor.cpp
	Source/OpenEXR/OpenEXR/ImfDwaCompressor.h
	Source/OpenEXR/OpenEXR/ImfDwaCompressorSimd.h
	Source/OpenEXR/OpenEXR/ImfEnvmapAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfEnvmapAttribute.h
	Source/OpenEXR/OpenEXR/ImfEnvmap.cpp
	Source/OpenEXR/OpenEXR/ImfEnvmap.h
	Source/OpenEXR/OpenEXR/ImfExport.h
	Source/OpenEXR/OpenEXR/ImfFastHuf.cpp
	Source/OpenEXR/OpenEXR/ImfFastHuf.h
	Source/OpenEXR/OpenEXR/ImfFloatAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfFloatAttribute.h
	Source/OpenEXR/OpenEXR/ImfFloatVectorAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfFloatVectorAttribute.h
	Source/OpenEXR/OpenEXR/ImfForward.h
	Source/OpenEXR/OpenEXR/ImfFrameBuffer.cpp
	Source/OpenEXR/OpenEXR/ImfFrameBuffer.h
	Source/OpenEXR/OpenEXR/ImfFramesPerSecond.cpp
	Source/OpenEXR/OpenEXR/ImfFramesPerSecond.h
	Source/OpenEXR/OpenEXR/ImfGenericInputFile.cpp
	Source/OpenEXR/OpenEXR/ImfGenericInputFile.h
	Source/OpenEXR/OpenEXR/ImfGenericOutputFile.cpp
	Source/OpenEXR/OpenEXR/ImfGenericOutputFile.h
	Source/OpenEXR/OpenEXR/ImfHeader.cpp
	Source/OpenEXR/OpenEXR/ImfHeader.h
	Source/OpenEXR/OpenEXR/ImfHuf.cpp
	Source/OpenEXR/OpenEXR/ImfHuf.h
	Source/OpenEXR/OpenEXR/ImfIDManifestAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfIDManifestAttribute.h
	Source/OpenEXR/OpenEXR/ImfIDManifest.cpp
	Source/OpenEXR/OpenEXR/ImfIDManifest.h
	Source/OpenEXR/OpenEXR/ImfInputFile.cpp
	Source/OpenEXR/OpenEXR/ImfInputFile.h
	Source/OpenEXR/OpenEXR/ImfInputPart.cpp
	Source/OpenEXR/OpenEXR/ImfInputPartData.cpp
	Source/OpenEXR/OpenEXR/ImfInputPartData.h
	Source/OpenEXR/OpenEXR/ImfInputPart.h
	Source/OpenEXR/OpenEXR/ImfInputStreamMutex.h
	Source/OpenEXR/OpenEXR/ImfInt64.h
	Source/OpenEXR/OpenEXR/ImfIntAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfIntAttribute.h
	Source/OpenEXR/OpenEXR/ImfIO.cpp
	Source/OpenEXR/OpenEXR/ImfIO.h
	Source/OpenEXR/OpenEXR/ImfKeyCodeAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfKeyCodeAttribute.h
	Source/OpenEXR/OpenEXR/ImfKeyCode.cpp
	Source/OpenEXR/OpenEXR/ImfKeyCode.h
	Source/OpenEXR/OpenEXR/ImfLineOrderAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfLineOrderAttribute.h
	Source/OpenEXR/OpenEXR/ImfLineOrder.h
	Source/OpenEXR/OpenEXR/ImfLut.cpp
	Source/OpenEXR/OpenEXR/ImfLut.h
	Source/OpenEXR/OpenEXR/ImfMatrixAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfMatrixAttribute.h
	Source/OpenEXR/OpenEXR/ImfMisc.cpp
	Source/OpenEXR/OpenEXR/ImfMisc.h
	Source/OpenEXR/OpenEXR/ImfMultiPartInputFile.cpp
	Source/OpenEXR/OpenEXR/ImfMultiPartInputFile.h
	Source/OpenEXR/OpenEXR/ImfMultiPartOutputFile.cpp
	Source/OpenEXR/OpenEXR/ImfMultiPartOutputFile.h
	Source/OpenEXR/OpenEXR/ImfMultiView.cpp
	Source/OpenEXR/OpenEXR/ImfMultiView.h
	Source/OpenEXR/OpenEXR/ImfName.h
	Source/OpenEXR/OpenEXR/ImfNamespace.h
	Source/OpenEXR/OpenEXR/ImfOpaqueAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfOpaqueAttribute.h
	Source/OpenEXR/OpenEXR/ImfOptimizedPixelReading.h
	Source/OpenEXR/OpenEXR/ImfOutputFile.cpp
	Source/OpenEXR/OpenEXR/ImfOutputFile.h
	Source/OpenEXR/OpenEXR/ImfOutputPart.cpp
	Source/OpenEXR/OpenEXR/ImfOutputPartData.cpp
	Source/OpenEXR/OpenEXR/ImfOutputPartData.h
	Source/OpenEXR/OpenEXR/ImfOutputPart.h
	Source/OpenEXR/OpenEXR/ImfOutputStreamMutex.h
	Source/OpenEXR/OpenEXR/ImfPartHelper.h
	Source/OpenEXR/OpenEXR/ImfPartType.cpp
	Source/OpenEXR/OpenEXR/ImfPartType.h
	Source/OpenEXR/OpenEXR/ImfPixelType.h
	Source/OpenEXR/OpenEXR/ImfPizCompressor.cpp
	Source/OpenEXR/OpenEXR/ImfPizCompressor.h
	Source/OpenEXR/OpenEXR/ImfPreviewImageAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfPreviewImageAttribute.h
	Source/OpenEXR/OpenEXR/ImfPreviewImage.cpp
	Source/OpenEXR/OpenEXR/ImfPreviewImage.h
	Source/OpenEXR/OpenEXR/ImfPxr24Compressor.cpp
	Source/OpenEXR/OpenEXR/ImfPxr24Compressor.h
	Source/OpenEXR/OpenEXR/ImfRationalAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfRationalAttribute.h
	Source/OpenEXR/OpenEXR/ImfRational.cpp
	Source/OpenEXR/OpenEXR/ImfRational.h
	Source/OpenEXR/OpenEXR/ImfRgbaFile.cpp
	Source/OpenEXR/OpenEXR/ImfRgbaFile.h
	Source/OpenEXR/OpenEXR/ImfRgba.h
	Source/OpenEXR/OpenEXR/ImfRgbaYca.cpp
	Source/OpenEXR/OpenEXR/ImfRgbaYca.h
	Source/OpenEXR/OpenEXR/ImfRleCompressor.cpp
	Source/OpenEXR/OpenEXR/ImfRleCompressor.h
	Source/OpenEXR/OpenEXR/ImfRle.cpp
	Source/OpenEXR/OpenEXR/ImfRle.h
	Source/OpenEXR/OpenEXR/ImfScanLineInputFile.cpp
	Source/OpenEXR/OpenEXR/ImfScanLineInputFile.h
	Source/OpenEXR/OpenEXR/ImfSimd.h
	Source/OpenEXR/OpenEXR/ImfStandardAttributes.cpp
	Source/OpenEXR/OpenEXR/ImfStandardAttributes.h
	Source/OpenEXR/OpenEXR/ImfStdIO.cpp
	Source/OpenEXR/OpenEXR/ImfStdIO.h
	Source/OpenEXR/OpenEXR/ImfStringAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfStringAttribute.h
	Source/OpenEXR/OpenEXR/ImfStringVectorAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfStringVectorAttribute.h
	Source/OpenEXR/OpenEXR/ImfSystemSpecific.cpp
	Source/OpenEXR/OpenEXR/ImfSystemSpecific.h
	Source/OpenEXR/OpenEXR/ImfTestFile.cpp
	Source/OpenEXR/OpenEXR/ImfTestFile.h
	Source/OpenEXR/OpenEXR/ImfThreading.cpp
	Source/OpenEXR/OpenEXR/ImfThreading.h
	Source/OpenEXR/OpenEXR/ImfTileDescriptionAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfTileDescriptionAttribute.h
	Source/OpenEXR/OpenEXR/ImfTileDescription.h
	Source/OpenEXR/OpenEXR/ImfTiledInputFile.cpp
	Source/OpenEXR/OpenEXR/ImfTiledInputFile.h
	Source/OpenEXR/OpenEXR/ImfTiledInputPart.cpp
	Source/OpenEXR/OpenEXR/ImfTiledInputPart.h
	Source/OpenEXR/OpenEXR/ImfTiledMisc.cpp
	Source/OpenEXR/OpenEXR/ImfTiledMisc.h
	Source/OpenEXR/OpenEXR/ImfTiledOutputFile.cpp
	Source/OpenEXR/OpenEXR/ImfTiledOutputFile.h
	Source/OpenEXR/OpenEXR/ImfTiledOutputPart.cpp
	Source/OpenEXR/OpenEXR/ImfTiledOutputPart.h
	Source/OpenEXR/OpenEXR/ImfTiledRgbaFile.cpp
	Source/OpenEXR/OpenEXR/ImfTiledRgbaFile.h
	Source/OpenEXR/OpenEXR/ImfTileOffsets.cpp
	Source/OpenEXR/OpenEXR/ImfTileOffsets.h
	Source/OpenEXR/OpenEXR/ImfTimeCodeAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfTimeCodeAttribute.h
	Source/OpenEXR/OpenEXR/ImfTimeCode.cpp
	Source/OpenEXR/OpenEXR/ImfTimeCode.h
	Source/OpenEXR/OpenEXR/ImfVecAttribute.cpp
	Source/OpenEXR/OpenEXR/ImfVecAttribute.h
	Source/OpenEXR/OpenEXR/ImfVersion.cpp
	Source/OpenEXR/OpenEXR/ImfVersion.h
	Source/OpenEXR/OpenEXR/ImfWav.cpp
	Source/OpenEXR/OpenEXR/ImfWav.h
	Source/OpenEXR/OpenEXR/ImfXdr.h
	Source/OpenEXR/OpenEXR/ImfZipCompressor.cpp
	Source/OpenEXR/OpenEXR/ImfZipCompressor.h
	Source/OpenEXR/OpenEXR/ImfZip.cpp
	Source/OpenEXR/OpenEXR/ImfZip.h
	Source/OpenEXR/OpenEXRCore/backward_compatibility.h
	Source/OpenEXR/OpenEXRCore/base.c
	Source/OpenEXR/OpenEXRCore/channel_list.c
	Source/OpenEXR/OpenEXRCore/chunk.c
	Source/OpenEXR/OpenEXRCore/coding.c
	Source/OpenEXR/OpenEXRCore/context.c
	Source/OpenEXR/OpenEXRCore/debug.c
	Source/OpenEXR/OpenEXRCore/decoding.c
	Source/OpenEXR/OpenEXRCore/encoding.c
	Source/OpenEXR/OpenEXRCore/float_vector.c
	Source/OpenEXR/OpenEXRCore/internal_attr.h
	Source/OpenEXR/OpenEXRCore/internal_b44.c
	Source/OpenEXR/OpenEXRCore/internal_b44_table.c
	Source/OpenEXR/OpenEXRCore/internal_channel_list.h
	Source/OpenEXR/OpenEXRCore/internal_coding.h
	Source/OpenEXR/OpenEXRCore/internal_compress.h
	Source/OpenEXR/OpenEXRCore/internal_constants.h
	Source/OpenEXR/OpenEXRCore/internal_decompress.h
	Source/OpenEXR/OpenEXRCore/internal_dwa.c
	Source/OpenEXR/OpenEXRCore/internal_file.h
	Source/OpenEXR/OpenEXRCore/internal_float_vector.h
	Source/OpenEXR/OpenEXRCore/internal_huf.c
	Source/OpenEXR/OpenEXRCore/internal_huf.h
	Source/OpenEXR/OpenEXRCore/internal_memory.h
	Source/OpenEXR/OpenEXRCore/internal_opaque.h
	Source/OpenEXR/OpenEXRCore/internal_piz.c
	Source/OpenEXR/OpenEXRCore/internal_posix_file_impl.h
	Source/OpenEXR/OpenEXRCore/internal_preview.h
	Source/OpenEXR/OpenEXRCore/internal_pxr24.c
	Source/OpenEXR/OpenEXRCore/internal_rle.c
	Source/OpenEXR/OpenEXRCore/internal_string.h
	Source/OpenEXR/OpenEXRCore/internal_string_vector.h
	Source/OpenEXR/OpenEXRCore/internal_structs.c
	Source/OpenEXR/OpenEXRCore/internal_structs.h
	Source/OpenEXR/OpenEXRCore/internal_win32_file_impl.h
	Source/OpenEXR/OpenEXRCore/internal_xdr.h
	Source/OpenEXR/OpenEXRCore/internal_zip.c
	Source/OpenEXR/OpenEXRCore/memory.c
	Source/OpenEXR/OpenEXRCore/opaque.c
	Source/OpenEXR/OpenEXRCore/openexr_attr.h
	Source/OpenEXR/OpenEXRCore/openexr_base.h
	Source/OpenEXR/OpenEXRCore/openexr_chunkio.h
	Source/OpenEXR/OpenEXRCore/openexr_coding.h
	Source/OpenEXR/OpenEXRCore/openexr_conf.h
	Source/OpenEXR/OpenEXRCore/openexr_context.h
	Source/OpenEXR/OpenEXRCore/openexr_debug.h
	Source/OpenEXR/OpenEXRCore/openexr_decode.h
	Source/OpenEXR/OpenEXRCore/openexr_encode.h
	Source/OpenEXR/OpenEXRCore/openexr_errors.h
	Source/OpenEXR/OpenEXRCore/openexr.h
	Source/OpenEXR/OpenEXRCore/openexr_part.h
	Source/OpenEXR/OpenEXRCore/openexr_std_attr.h
	Source/OpenEXR/OpenEXRCore/pack.c
	Source/OpenEXR/OpenEXRCore/parse_header.c
	Source/OpenEXR/OpenEXRCore/part_attr.c
	Source/OpenEXR/OpenEXRCore/part.c
	Source/OpenEXR/OpenEXRCore/preview.c
	Source/OpenEXR/OpenEXRCore/std_attr.c
	Source/OpenEXR/OpenEXRCore/string.c
	Source/OpenEXR/OpenEXRCore/string_vector.c
	Source/OpenEXR/OpenEXRCore/unpack.c
	Source/OpenEXR/OpenEXRCore/validation.c
	Source/OpenEXR/OpenEXRCore/write_header.c
	Source/OpenEXR/OpenEXRUtil/ImfCheckFile.cpp
	Source/OpenEXR/OpenEXRUtil/ImfCheckFile.h
	Source/OpenEXR/OpenEXRUtil/ImfDeepImageChannel.cpp
	Source/OpenEXR/OpenEXRUtil/ImfDeepImageChannel.h
	Source/OpenEXR/OpenEXRUtil/ImfDeepImage.cpp
	Source/OpenEXR/OpenEXRUtil/ImfDeepImage.h
	Source/OpenEXR/OpenEXRUtil/ImfDeepImageIO.cpp
	Source/OpenEXR/OpenEXRUtil/ImfDeepImageIO.h
	Source/OpenEXR/OpenEXRUtil/ImfDeepImageLevel.cpp
	Source/OpenEXR/OpenEXRUtil/ImfDeepImageLevel.h
	Source/OpenEXR/OpenEXRUtil/ImfFlatImageChannel.cpp
	Source/OpenEXR/OpenEXRUtil/ImfFlatImageChannel.h
	Source/OpenEXR/OpenEXRUtil/ImfFlatImage.cpp
	Source/OpenEXR/OpenEXRUtil/ImfFlatImage.h
	Source/OpenEXR/OpenEXRUtil/ImfFlatImageIO.cpp
	Source/OpenEXR/OpenEXRUtil/ImfFlatImageIO.h
	Source/OpenEXR/OpenEXRUtil/ImfFlatImageLevel.cpp
	Source/OpenEXR/OpenEXRUtil/ImfFlatImageLevel.h
	Source/OpenEXR/OpenEXRUtil/ImfImageChannel.cpp
	Source/OpenEXR/OpenEXRUtil/ImfImageChannel.h
	Source/OpenEXR/OpenEXRUtil/ImfImageChannelRenaming.h
	Source/OpenEXR/OpenEXRUtil/ImfImage.cpp
	Source/OpenEXR/OpenEXRUtil/ImfImageDataWindow.cpp
	Source/OpenEXR/OpenEXRUtil/ImfImageDataWindow.h
	Source/OpenEXR/OpenEXRUtil/ImfImage.h
	Source/OpenEXR/OpenEXRUtil/ImfImageIO.cpp
	Source/OpenEXR/OpenEXRUtil/ImfImageIO.h
	Source/OpenEXR/OpenEXRUtil/ImfImageLevel.cpp
	Source/OpenEXR/OpenEXRUtil/ImfImageLevel.h
	Source/OpenEXR/OpenEXRUtil/ImfSampleCountChannel.cpp
	Source/OpenEXR/OpenEXRUtil/ImfSampleCountChannel.h
	Source/OpenEXR/OpenEXRUtil/ImfUtilExport.h
	Source/Plugin.h
	Source/Quantizers.h
	Source/ToneMapping.h
	Source/Utilities.h
)

if( WIN32 )
	set( FreeImage_SOURCES ${FreeImage_SOURCES}
		Source/OpenEXR/IlmThread/IlmThreadSemaphoreWin32.cpp
	)
else()
	set( FreeImage_SOURCES ${FreeImage_SOURCES}
		Source/OpenEXR/IlmThread/IlmThread.cpp
		Source/OpenEXR/IlmThread/IlmThreadSemaphore.cpp
		Source/OpenEXR/IlmThread/IlmThreadSemaphorePosix.cpp
		Source/OpenEXR/IlmThread/IlmThreadSemaphorePosixCompat.cpp
		Source/OpenEXR/IlmThread/IlmThreadSemaphoreOSX.cpp
	)
endif()

if (APPLE AND NOT OGRE_BUILD_PLATFORM_APPLE_IOS)
    # On macOS, provide sources for both Arm and Intel,
    # regardless of CMAKE_SYSTEM_PROCESSOR.
	set( FreeImage_SOURCES ${FreeImage_SOURCES}
		Source/LibPNG/arm/arm_init.c
		Source/LibPNG/arm/filter_neon_intrinsics.c
		Source/LibPNG/arm/palette_neon_intrinsics.c
		Source/LibPNG/intel/filter_sse2_intrinsics.c
		Source/LibPNG/intel/intel_init.c
	)
elseif( CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64" OR OGRE_BUILD_PLATFORM_APPLE_IOS )
	set( FreeImage_SOURCES ${FreeImage_SOURCES}
		Source/LibPNG/arm/arm_init.c
		Source/LibPNG/arm/filter_neon_intrinsics.c
		Source/LibPNG/arm/palette_neon_intrinsics.c
	)
else()
	set( FreeImage_SOURCES ${FreeImage_SOURCES}
		Source/LibPNG/intel/filter_sse2_intrinsics.c
		Source/LibPNG/intel/intel_init.c
	)
endif()

# need include directories for FreeImage and all the sub libs
include_directories(Source)
include_directories(Source/FreeImageToolkit)
include_directories(Source/LibJPEG)
include_directories(Source/LibJXR)
include_directories(Source/LibJXR/jxrgluelib)
include_directories(Source/LibJXR/image/sys)
include_directories(Source/LibJXR/common/include)
include_directories(Source/LibJXR/image)
include_directories(Source/LibJXR/image/decode)
include_directories(Source/LibJXR/image/encode)
include_directories(Source/LibJXR/image/x86)
include_directories(Source/LibMNG)
include_directories(Source/LibPNG)
include_directories(Source/LibRawLite)
include_directories(Source/LibTIFF4)
include_directories(Source/LibWebP)
include_directories(Source/LibWebP/src)
include_directories(Source/OpenEXR)
include_directories(Source/OpenEXR/Iex)
include_directories(Source/OpenEXR/IlmThread)
include_directories(Source/OpenEXR/Imath)
include_directories(Source/OpenEXR/OpenEXR)
include_directories(Source/OpenEXR/OpenEXRCore)
include_directories(Source/openjp2)
include_directories(../zlib)

add_definitions(-DOPJ_STATIC -DLIBRAW_NODLL -DLIBRAW_LIBRARY_BUILD -DFREEIMAGE_LIB -DNO_LCMS -DPNG_INTEL_SSE_OPT=1)
add_definitions("-DFREEIMAGERE_MAJOR_VERSION=${FREEIMAGERE_MAJOR_VERSION}")
add_definitions("-DFREEIMAGERE_MINOR_VERSION=${FREEIMAGERE_MINOR_VERSION}")

# ======== BEGIN openjpeg definitions ========
# _aligned_alloc https://msdn.microsoft.com/en-us/library/8z34s9c6.aspx
check_symbol_exists(_aligned_malloc malloc.h OPJ_HAVE__ALIGNED_MALLOC)
if( OPJ_HAVE__ALIGNED_MALLOC )
    add_definitions( "-DOPJ_HAVE__ALIGNED_MALLOC=1" )
endif()
# posix_memalign (needs _POSIX_C_SOURCE >= 200112L on Linux)
check_symbol_exists(memalign malloc.h OPJ_HAVE_MEMALIGN)
if( OPJ_HAVE_MEMALIGN )
    add_definitions( "-DOPJ_HAVE_MEMALIGN=1" )
endif()
# memalign (obsolete)
check_symbol_exists(posix_memalign stdlib.h OPJ_HAVE_POSIX_MEMALIGN)
if( OPJ_HAVE_POSIX_MEMALIGN )
    add_definitions( "-DOPJ_HAVE_POSIX_MEMALIGN=1" )
endif()
# ========= END openjpeg definitions =========

# LibJXR
add_definitions( "-DDISABLE_PERF_MEASUREMENT" )
if( NOT MSVC )
    add_definitions( "-D__ANSI__=1" )
endif()

# ======== BEGIN OpenEXR definitions ========
check_include_files(ucontext.h IEX_HAVE_UCONTEXT_H)
if(IEX_HAVE_UCONTEXT_H)
  check_struct_has_member("struct _libc_fpstate" mxcsr ucontext.h IEX_HAVE_CONTROL_REGISTER_SUPPORT)
  if(NOT IEX_HAVE_CONTROL_REGISTER_SUPPORT)
    check_include_files(asm/sigcontext.h IEX_HAVE_SIGCONTEXT_H)
    if(IEX_HAVE_SIGCONTEXT_H)
      check_struct_has_member("struct _fpstate" mxcsr asm/sigcontext.h IEX_HAVE_SIGCONTEXT_CONTROL_REGISTER_SUPPORT)
    endif()
  endif()


  add_definitions( "-DHAVE_UCONTEXT_H=1" )
  if( IEX_HAVE_CONTROL_REGISTER_SUPPORT )
      add_definitions( "-DIEX_HAVE_CONTROL_REGISTER_SUPPORT=1" )
  endif()
  if( IEX_HAVE_SIGCONTEXT_CONTROL_REGISTER_SUPPORT )
      add_definitions( "-DIEX_HAVE_SIGCONTEXT_CONTROL_REGISTER_SUPPORT=1" )
  endif()
endif()

if( UNIX AND NOT APPLE )
    add_definitions( "-DILMTHREAD_HAVE_POSIX_SEMAPHORES=1" )
endif()

if( APPLE )
    add_definitions( "-DOPENEXR_IMF_HAVE_DARWIN=1" )
endif()

check_cxx_source_compiles(
"
#include <unistd.h>
int main()
{
	sysconf(_SC_NPROCESSORS_ONLN);
}
" OPENEXR_IMF_HAVE_SYSCONF_NPROCESSORS_ONLN
)

if( OPENEXR_IMF_HAVE_SYSCONF_NPROCESSORS_ONLN )
	add_definitions( "-DOPENEXR_IMF_HAVE_SYSCONF_NPROCESSORS_ONLN=1" )
endif()

check_cxx_source_compiles(
"
int main()
{
#if defined(__SSE2__)
    int n   = 0;
    int eax = 0;
    int edx = 0;
    __asm__(
        \"xgetbv     ;\"
        \"vzeroupper  \"
        : \"=a\"(eax), \"=d\"(edx) : \"c\"(n) : );
#else
#    error No SSE support enabled to query AVX support
#endif
}
" OPENEXR_IMF_HAVE_GCC_INLINE_ASM_AVX
)

if( OPENEXR_IMF_HAVE_GCC_INLINE_ASM_AVX )
	add_definitions( "-DOPENEXR_IMF_HAVE_GCC_INLINE_ASM_AVX=1" )
endif()

# ========= END OpenEXR definitions =========

add_library(FreeImage STATIC ${FreeImage_SOURCES})
if (OGRE_PROJECT_FOLDERS)
	set_property(TARGET FreeImage PROPERTY FOLDER Dependencies)
endif ()

install_dep(FreeImage include Source/FreeImage.h)

if (APPLE)
 set_target_properties(FreeImage PROPERTIES XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO")

 if(OGRE_BUILD_PLATFORM_APPLE_IOS)
  set_target_properties(FreeImage PROPERTIES XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT "NO")
 endif()
endif()

set(FreeImage_INCLUDE_DIR "${FreeImage_SOURCE_DIR}/Source" CACHE PATH "" FORCE)
set(FreeImage_LIBRARY_DBG FreeImage CACHE STRING "" FORCE)
set(FreeImage_LIBRARY_REL FreeImage CACHE STRING "" FORCE)
mark_as_advanced(FreeImage_INCLUDE_DIR FreeImage_LIBRARY_DBG FreeImage_LIBRARY_REL)
