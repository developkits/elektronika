/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						"elektroexp.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	SELPAD.CPP					(c)	YoY'04						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<stdio.h>
#include						"selpad.h"
#include						"paddle.h"
#include						"interface.h"
#include						"../alib/resource.h"
#include						"resource.h"
#include						"effect.h"
#include						"elektro.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL ACI						Aselpad::CI=ACI("Aselpad", GUID(0xE4EC7600,0x00010130), &AcontrolObj::CI, 0, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aselpad::Aselpad(QIID qiid, char *name, Aobject *L, int x, int y, int nstep, int type) : AcontrolObj(name, L, x, y, 4, 4)
{
	bmp=null;
	this->nstep=0;
	switch(type)
	{
		case paddleBUTTON01:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PADDLE001), "PNG");
			size(32, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleBUTTON02:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PADDLE002), "PNG");
			size(32, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleBUTTON03:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PADDLE003), "PNG");
			size(64, 64);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleBUTTON04:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PADDLE004), "PNG");
			bmp=new Abitmap(&o);
			size(32, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleBUTTON05:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PADDLE005), "PNG");
			size(32, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleBUTTON06:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PADDLE006), "PNG");
			size(32, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleBUTTON07:
		{
			Aresobj	o=alibres.get(MAKEINTRESOURCE(PNG_PADDLE007), "PNG");
			size(16, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleELEK32:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(IDR_PNG1), "PNG");
			size(32, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleELEK24:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(IDR_PNG2), "PNG");
			size(24, 24);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleELEK16:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(IDR_PNG3), "PNG");
			size(16, 16);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleELEK12:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(IDR_PNG4), "PNG");
			size(12, 12);
			init(qiid, name, L, &o, nstep);
		}
		break;
		
		case paddleYOLI16:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(PNG_YOLI16), "PNG");
			size(16, 16);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleYOLI24:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(PNG_YOLI24), "PNG");
			size(24, 24);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleYOLI32:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(PNG_YOLI32), "PNG");
			size(32, 32);
			init(qiid, name, L, &o, nstep);
		}
		break;

		case paddleYOLI64:
		{
			Aresobj	o=resdll.get(MAKEINTRESOURCE(PNG_YOLI64), "PNG");
			size(64, 64);
			init(qiid, name, L, &o, nstep);
		}
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aselpad::Aselpad(QIID qiid, char *name, Aobject *L, int x, int y, int w, int h, Aresobj *o, int nstep) : AcontrolObj(name, L, x, y, w, h)
{
	init(qiid, name, L, o, nstep);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Aselpad::init(qword qiid, char *name, Aobject *L, Aresobj *o, int nstep)
{
	test=false;
	y0=0;
	step0=0;
	this->nstep=nstep;
	istep=0;
	control=new Acontrol(qiid, name, Aeffect::getEffect(L), this, Acontrol::KEY_01+nstep);
	bmp=new Abitmap(o);
	set(0);
	defvalue=-1;
	ctrlPaint=false;
	timer(CTRLTIMEREPAINT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL Aselpad::~Aselpad()
{
	delete(control);
	if(bmp)
		delete(bmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool Aselpad::keyboard(int event, int ascii, int scan, int state)
{
	switch(event)
	{
		case keyboardDOWN:
		if(state&keyboardALT)
		{
			if(defvalue!=-1)
				set(defvalue);
			else
				set(0);
			father->notify(this, nyCHANGE);
			return true;
		}
		break;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool Aselpad::mouse(int x, int y, int state, int event)
{
	switch(event)
	{
		case mouseLDOWN:
		control->select();
		y0=y;
		step0=istep;
		test=true;
		mouseCapture(true);
		cursor(cursorHANDSEL);
		return true;

		case mouseNORMAL:
		cursor(cursorHANDSEL);
		focus(this);
		if(getKeyboardState()&keyboardLALT)
		{
			if(defvalue!=-1)
				set(defvalue);
			else
				set(0);
			father->notify(this, nyCHANGE);
			return true;
		}
		if(test)
		{
			istep=mini(maxi((int)(step0-alib.mouseSensibility*(float)(y-y0)*(float)nstep), 0), nstep-1);
			control->set(Acontrol::KEY, (float)istep);
			father->notify(this, nyCHANGE);
			repaint();
		}
		return true;

		case mouseLUP:
		case mouseLEAVE:
		test=false;
		mouseCapture(false);
		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Aselpad::set(int n)
{
	istep=n%nstep;
	if(defvalue==-1)
		defvalue=istep;
	control->set(Acontrol::KEY, (float)istep);
	repaint();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL int Aselpad::get()
{
	return istep;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL bool Aselpad::sequence(int nctrl, float value)
{
	istep=(int)value;
	father->notify(this, nyCHANGE, istep);
	ctrlPaint=true;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Aselpad::pulse()
{
	if(ctrlPaint)
	{
		repaint();
		ctrlPaint=false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EDLL void Aselpad::paint(Abitmap *bitmap)
{
	if(bmp)
	{
		int	max=bmp->w/pos.w;
		int	n=mini(istep*(max-1)/(nstep-1), max-1);
		bitmap->set(0, 0, pos.w, pos.h, pos.w*n, 0, pos.w, pos.h, bmp);
	}
	controlPaint(bitmap, pos.w, pos.h);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
