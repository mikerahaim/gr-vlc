/* -*- c++ -*- */

#define VLC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "vlc_swig_doc.i"

%{
#include "vlc/channel_fixed.h"
#include "vlc/channel_static.h"
#include "vlc/channel_relative.h"
%}


%include "vlc/channel_fixed.h"
GR_SWIG_BLOCK_MAGIC2(vlc, channel_fixed);
%include "vlc/channel_static.h"
GR_SWIG_BLOCK_MAGIC2(vlc, channel_static);
%include "vlc/channel_relative.h"
GR_SWIG_BLOCK_MAGIC2(vlc, channel_relative);
