// File: Magick.hh
// Date: Wed Apr 10 19:22:58 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#pragma once
#include "render/render.hh"
#include <Magick++.h>
#include <cstring>
using namespace Magick;


class MagickRender : public RenderBase {
	private:
		Image img;
		std::string fname;
		int w;
		Pixels *view;
		PixelPacket *pixels_ptr;

	public:
		MagickRender(const ::Geometry& g, const char* m_fname):
			RenderBase(g),
			img(Magick::Geometry(g.w, g.h), "black"),
			 fname(m_fname),w(g.w) {
			img.type(TrueColorType);
			img.modifyImage();
			view = new Pixels(img);
			pixels_ptr = view->get(0, 0, g.w, g.h);
		}

		MagickRender(int w, int h, const char* fname):
			MagickRender(::Geometry(w, h), fname){}

		~MagickRender()
		{ delete view; }

		void finish() {
			view->sync();
			img.write(fname.c_str());
		}

	private:
		void _write(int x, int y, const ::Color &c)
		{ pixels_ptr[y * w + x] = ColorRGB(c.x, c.y, c.z); }

};

