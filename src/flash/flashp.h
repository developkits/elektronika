/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	MAIN.H						(c)	YoY'02						WEB: www.aestesis.org
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef							_MAIN_H_
#define							_MAIN_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include						<interface.h>
#include						<elektro.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define							guidFLASHP						(Aflashp::CI.guid)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern Aresource				resdll;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aflashp : public Aeffect
{
	AOBJ

								Aflashp							(QIID qiid, char *name, AeffectInfo *info, Acapsule *capsule);
	virtual						~Aflashp						();

	virtual bool				load							(class Afile *f);
	virtual bool				save							(class Afile *f);

	virtual bool				loadPreset						(class Afile *f);
	virtual bool				savePreset						(class Afile *f);

	virtual void				actionStart						(double time);
	virtual void				action							(double time, double dtime, double beat, double dbeat);
	virtual void				actionStop						();
	virtual void				settings						(bool emergency);

	virtual int					priority						() { return priorityFILTER; }

	void						command							(char *name, char *value);

	void						initSWF							(int w, int h);
	void						delSWF							();
	void						getBitmap						(Abitmap *b);

	class CShockwaveFlash		*swf;
	char						filename[8][ALIB_PATH];
	
	char						*text;
	
	int							bass;
	int							medium;
	int							treble;
	double						time;
	double						beat;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AflashFront : public AeffectFront
{
public:
	AOBJ
	
	enum
	{
								modeSTOPPED,
								modeSTOP,
								modeSTART,
								modeRUNNING
	};
	

								AflashFront						(QIID qiid, char *name, Aflashp *e, int h);
	virtual						~AflashFront					();

	virtual bool				dragdrop						(int x, int y, int state, int event, void *data=NULL);
	void						paint							(Abitmap *b);
	bool						notify							(Anode *o, int event, dword p);

	virtual void				pulse							();

	void						computeDrop						(int n, void *data);
	void						loadflash						();
	void						updatePad						();
	
	Asection					sectionC;
	Abitmap						*back;

	Aselect						*select;
	Astatic						*file;
	Astatic						*vtext;

	Apaddle						*zoom;

	class Aflashm				*flashm[8];

	Abutton						*btext;
	class Amtext				*mtext;

	char						flashtips[6][128];
	char						flashvisible[16];
	dword						flashflag;
	int							flashmode;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AflashBack : public AeffectBack
{
	AOBJ

								AflashBack						(QIID qiid, char *name, Aflashp *e, int h);
	virtual						~AflashBack						();

	void						paint							(Abitmap *b);

	Abitmap						*back;

	Avideo						*out;
	Asample						*in;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AflashInfo : public AeffectInfo
{
	AOBJ 

								AflashInfo						(char *name, ACI *eci, char *ename, char *ehelp);
	virtual int					getEffectClass					() { return PLAYER; }
	virtual dword				version							() { return 0x00019900; }

	virtual Aeffect *			create							(QIID qiid, char *name, Acapsule *capsule);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__inline AflashInfo::AflashInfo(char *name, ACI *eci, char *ename, char *ehelp) : AeffectInfo(name, eci, ename, ehelp)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" 
{
	DLLEXPORT class Aplugz *	getPlugz						();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif							//_MAIN_H
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////