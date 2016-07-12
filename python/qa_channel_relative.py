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

class qa_channel_relative (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        phi = 90;
        psi = 90;
        d   = 1;
        m   = 1;
        A   = 1;
        n   = 1;
        FOV = 90;
        Ts  = 1;
        R   = 1;
        src_data = (1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0)
        expected_result = (0,0,0,0,0,0,0,0,0,0)

        src = blocks.vector_source_f(src_data)
        blk = vlc.channel_relative(phi, psi, d, m, A, n, FOV, Ts, R)
        dst = blocks.vector_sink_f()
                
        self.tb.connect(src, blk)
        self.tb.connect(blk, dst)
        self.tb.run()
        result_data = dst.data()
        
        print "Source: "
        print str(src_data).strip('[]')
        print "Results: "
        print str(result_data).strip('[]')
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)
        
    def test_002_t (self):
        phi = 10;
        psi = 20;
        d   = 1;
        m   = 1;
        A   = 1;
        n   = 1;
        FOV = 90;
        Ts  = 1;
        R   = 1;
        src_data = (1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0)
        expected_result = (0,0,0,0,0,0,0,0,0,0)

        src = blocks.vector_source_f(src_data)
        blk = vlc.channel_relative(phi, psi, d, m, A, n, FOV, Ts, R)
        dst = blocks.vector_sink_f()
        
        blk.set_phi(45)
        blk.set_psi(90)
        blk.set_d(5)
        
        print "Emission Angle: %f." % blk.phi()
        print "Acceptance Angle: %f." % blk.psi()
        print "Distance: %f." % blk.d()
        
        self.tb.connect(src, blk)
        self.tb.connect(blk, dst)
        self.tb.run()
        result_data = dst.data()
        
        print "Source: "
        print str(src_data).strip('[]')
        print "Results: "
        print str(result_data).strip('[]')
        self.assertFloatTuplesAlmostEqual(expected_result, result_data, 6)

if __name__ == '__main__':
    gr_unittest.run(qa_channel_relative, "qa_channel_relative.xml")
