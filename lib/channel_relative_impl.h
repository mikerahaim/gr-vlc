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

#ifndef INCLUDED_VLC_CHANNEL_RELATIVE_IMPL_H
#define INCLUDED_VLC_CHANNEL_RELATIVE_IMPL_H

#include <vlc/channel_relative.h>

namespace gr {
  namespace vlc {

    class channel_relative_impl : public channel_relative
    {
     private:
      float d_phi, d_psi, d_d;
      float d_m;
      float d_A, d_n, d_FOV, d_Ts;
      float d_R;
      float d_gain;

     public:
      channel_relative_impl(float phi, float psi, float d, float m, float A, float n, float FOV, float Ts, float R);
      ~channel_relative_impl();
      
      void set_phi(float phi) { d_phi = phi; update_gain(); }
      float phi() { return d_phi; }
      void set_psi(float psi) { d_psi = psi; update_gain(); }
      float psi() { return d_psi; }
      void set_d(float d) { d_d = d; update_gain(); }
      float d() { return d_d; }
      float update_gain();

      // Where all the action really happens
      int work(int noutput_items,
               gr_vector_const_void_star &input_items,
               gr_vector_void_star &output_items);
    };

  } // namespace vlc
} // namespace gr

#endif /* INCLUDED_VLC_CHANNEL_RELATIVE_IMPL_H */

