// File: viewer.hh
// Date: Mon Jun 10 21:22:22 2013 +0800
// Author: Yuxin Wu <ppwwyyxxc@gmail.com>

#pragma once
#include "view.hh"
#include "render/cvrender.hh"

class Viewer {
	protected:
		View& v;
		const Geometry& geo;
	public:
		Viewer(View& _v):
			v(_v), geo(_v.get_geo()){}

		virtual ~Viewer(){}

		Viewer(const Viewer&) = delete;

		Viewer & operator = (const Viewer&) = delete;

		virtual void view() = 0;

		virtual void render_all() = 0;

};

class CVViewer : public Viewer {
	private:
		CVRender r;
	public:
		CVViewer(View& _v):
			Viewer(_v), r(_v.get_geo()) { }

		CVViewer(View& _v, const char* fname):CVViewer(_v) {
			render_all();
			r.save(fname);
		}

		void view();

		void render_all();
};