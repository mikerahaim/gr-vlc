#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import vlc_swig as vlc
import math

class qa_channel_static (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        my_phi = 0;
        my_psi = 0;
        my_dist = 1;
        pi = math.pi;
        
        src_data = (1, 2, 3, 4, 5, 2.5, 5.234, 9.999)
        expected_result = (1/pi, 2/pi, 3/pi, 4/pi, 5/pi, 2.5/pi, 5.234/pi, 9.999/pi)
        src = blocks.vector_source_f(src_data)
        my_chan = vlc.channel_static(my_phi, my_psi, my_dist)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, my_chan)
        self.tb.connect(my_chan, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def test_002_t (self):
        my_phi = 0
        my_psi = 15
        my_dist = 1
        
        g_tx = 1/math.pi
        g_rx = 0.96592582628
        G = g_tx*g_rx/(my_dist*my_dist)
        
        src_data = (1, 2, 3, 4, 5, 2.5, 5.234, 9.999)
        expected_result = (1*G, 2*G, 3*G, 4*G, 5*G, 2.5*G, 5.234*G, 9.999*G)
        src = blocks.vector_source_f(src_data)
        my_chan = vlc.channel_static(my_phi, my_psi, my_dist)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, my_chan)
        self.tb.connect(my_chan, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)
        
    def test_003_t (self):
        my_phi = 30
        my_psi = 15
        my_dist = 1
        
        g_tx = 0.86602540378/math.pi
        g_rx = 0.96592582628
        G = g_tx*g_rx/(my_dist*my_dist)
        
        src_data = (1, 2, 3, 4, 5, 2.5, 5.234, 9.999)
        expected_result = (1*G, 2*G, 3*G, 4*G, 5*G, 2.5*G, 5.234*G, 9.999*G)
        src = blocks.vector_source_f(src_data)
        my_chan = vlc.channel_static(my_phi, my_psi, my_dist)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, my_chan)
        self.tb.connect(my_chan, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)        

if __name__ == '__main__':
    gr_unittest.run(qa_channel_static, "qa_channel_static.xml")
