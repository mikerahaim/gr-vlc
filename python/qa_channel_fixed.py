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

class qa_channel_fixed (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        my_gain = 2;
        src_data = (-3, 4, -5.5, 2.2, 3)
        expected_result = (-6, 8, -11, 4.4, 6)
        src = blocks.vector_source_f(src_data)
        my_chan = vlc.channel_fixed(my_gain)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, my_chan)
        self.tb.connect(my_chan, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def test_002_t (self):
        my_gain = 1;
        src_data = (-3, 4, -5.5, 2.2, 3)
        expected_result = (-3, 4, -5.5, 2.2, 3)
        src = blocks.vector_source_f(src_data)
        my_chan = vlc.channel_fixed(my_gain)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, my_chan)
        self.tb.connect(my_chan, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

    def test_003_t (self):
        my_gain = 0.22;
        src_data = (1, 2, 3, 4, 5, -1, 0, -2, 0.1)
        expected_result = (0.22, 0.44, 0.66, 0.88, 1.10, -0.22, 0, -0.44, 0.022)
        src = blocks.vector_source_f(src_data)
        my_chan = vlc.channel_fixed(my_gain)
        dst = blocks.vector_sink_f()
        self.tb.connect(src, my_chan)
        self.tb.connect(my_chan, dst)
        self.tb.run()
        result_data = dst.data()
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

if __name__ == '__main__':
    gr_unittest.run(qa_channel_fixed, "qa_channel_fixed.xml")
