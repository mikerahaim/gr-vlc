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
#include <cmath>
#include "channel_static_impl.h"

namespace gr {
  namespace vlc {

    channel_static::sptr
    channel_static::make(float emission_angle, float acceptance_angle, float distance)
    {
      return gnuradio::get_initial_sptr
        (new channel_static_impl(emission_angle, acceptance_angle, distance));
    }

    /*
     * The private constructor
     */
    channel_static_impl::channel_static_impl(float emission_angle, float acceptance_angle, float distance)
      : gr::sync_block("channel_static",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      double m = 1;
      float A = 1;
      //int n = 1;
      //int FOV = 60;
      float G_tx, G_rx;
      
      G_tx = ((m+1)/(2*M_PI))*pow(cos(double(emission_angle*M_PI/180)),m);
      G_rx = A*cos((double)acceptance_angle*M_PI/180);
      
      channel_static_impl::gain = G_tx*G_rx/(distance*distance);
    }

    /*
     * Our virtual destructor.
     */
    channel_static_impl::~channel_static_impl()
    {
    }

    int
    channel_static_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      for(int i = 0; i < noutput_items; i++) {
        out[i] = in[i] * channel_static_impl::gain;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace vlc */
} /* namespace gr */

