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


#ifndef INCLUDED_VLC_CHANNEL_RELATIVE_H
#define INCLUDED_VLC_CHANNEL_RELATIVE_H

#include <vlc/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace vlc {

    /*!
     * \brief VLC channel model with variable distance and emission / acceptance angle.
     * \ingroup vlc
     *
     */
    class VLC_API channel_relative : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<channel_relative> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of vlc::channel_relative.
       *
       * To avoid accidental use of raw pointers, vlc::channel_relative's
       * constructor is in a private implementation
       * class. vlc::channel_relative::make is the public interface for
       * creating new instances.
       */
      static sptr make(float phi, float psi, float d, float m, float A, float n, float FOV, float Ts, float R);
      
      virtual void set_phi(float phi) = 0;
      virtual float phi() = 0;
      virtual void set_psi(float psi) = 0;
      virtual float psi() = 0;
      virtual void set_d(float d) = 0;
      virtual float d() = 0;
      virtual void set_Ts(float Ts) = 0;
      virtual float Ts() = 0;
    };

  } // namespace vlc
} // namespace gr

#endif /* INCLUDED_VLC_CHANNEL_RELATIVE_H */

