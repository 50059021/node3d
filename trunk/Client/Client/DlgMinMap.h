//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once /* DlgMinMap.h */
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "UIDialog.h"
#include "TSingleton.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CDlgMinMap : public CUIDialog, public TSingleton<CDlgMinMap>
{
public:
	// ----
	virtual void OnControlRegister	();
	virtual bool OnInitDialog		();
	virtual void OnFrameMove		(double fTime, float fElapsedTime);
	virtual void OnFrameRender		(const Matrix& mTransform, double fTime, float fElapsedTime);
private:
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------