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
#include "channel_relative_impl.h"
#include <cmath>

namespace gr {
  namespace vlc {

    channel_relative::sptr
    channel_relative::make(float phi, float psi, float d, float m, float A, float n, float FOV, float Ts, float R)
    {
      return gnuradio::get_initial_sptr
        (new channel_relative_impl(phi, psi, d, m, A, n, FOV, Ts, R));
    }

    /*
     * The private constructor
     */
    channel_relative_impl::channel_relative_impl(float phi, float psi, float d, float m, float A, float n, float FOV, float Ts, float R)
      : gr::sync_block("channel_relative",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
      d_phi = phi;
      d_psi = psi;
      d_d   = d;
      d_m   = m;
      d_A   = A;
      d_n   = n;
      d_FOV = FOV;
      d_Ts  = Ts;
      d_R   = R;
      
      update_gain();
    }

    /*
     * Our virtual destructor.
     */
    channel_relative_impl::~channel_relative_impl()
    {
    }

    float channel_relative_impl::update_gain()
    {
      float Ho, G_tx, G_rx, gc;
      float phi_rad, psi_rad, FOV_rad;
      
      phi_rad = d_phi*(M_PI/180);
      psi_rad = d_psi*(M_PI/180);
      FOV_rad = d_FOV*(M_PI/180);
      
      // Transmitter gain
      G_tx = ((d_m+1)/(2*M_PI))*pow(cos(phi_rad), d_m);
      
      // Concentrator Gain
      if (d_psi <= d_FOV)
        gc  = (d_n*d_n)/pow(sin(FOV_rad), 2); 
      else
        gc = 0;
      
      // Receiver gain
      G_rx = d_A * d_Ts * gc * cos(psi_rad);
      
      // Calculate optical channel gain
      Ho = G_tx * G_rx / (d_d*d_d);
      
      // Set gain [A/W] (Note: d_gain = optical gain if d_R=1)
      d_gain = d_R*Ho;      
    }
    
    int
    channel_relative_impl::work(int noutput_items,
                                gr_vector_const_void_star &input_items,
                                gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      for (int i = 0; i < noutput_items; i++) {
        out[i] = in[i]*d_gain;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace vlc */
} /* namespace gr */

