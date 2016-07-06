/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "channel_fixed_impl.h"

namespace gr {
  namespace vlc {

    channel_fixed::sptr
    channel_fixed::make(float gain)
    {
      return gnuradio::get_initial_sptr
        (new channel_fixed_impl(gain));
    }

    /*
     * The private constructor
     */
    channel_fixed_impl::channel_fixed_impl(float gain)
      : gr::sync_block("channel_fixed",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      channel_fixed_impl::gain = gain;
	}

    /*
     * Our virtual destructor.
     */
    channel_fixed_impl::~channel_fixed_impl()
    {
    }

    int
    channel_fixed_impl::work(int noutput_items,
							 gr_vector_const_void_star &input_items,
							 gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      for(int i = 0; i < noutput_items; i++) {
        out[i] = in[i] * channel_fixed_impl::gain;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace vlc */
} /* namespace gr */

