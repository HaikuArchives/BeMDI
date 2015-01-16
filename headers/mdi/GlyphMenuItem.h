/***********************************************************************/
/* GlyphMenuItem.h                                                     */
/*                                                                     */
/* A menu item displaying a icon in front of its label.                */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#ifndef GLYPH_MENU_ITEM_H
#define GLYPH_MENU_ITEM_H

//! file=GlyphMenuItem.h

//: Menu item with an icon in front of the label
// Besides of the icon, this class be used to display a 'default' menu
// item. The label of the default item of a menu is displayed using a
// bold font.
class CGlyphMenuItem : public BMenuItem
{
	public:
	CGlyphMenuItem(const char *label, BBitmap *glyph_bm, 
					bool isDefaultEntry, BMessage *message=NULL, 
					char shortcut=0, uint32 modifiers=0,
					BPoint _offset=B_ORIGIN);

	//: Destructor
	virtual ~CGlyphMenuItem();
	
	protected:
	virtual void DrawContent();
	virtual void GetContentSize(float *width, float *height);
	
	BFont SetDrawFont();
	
	//: Icon displayed in front of the label.
	BBitmap *glyph;
	
	//: If this member is 'true', the label is drawn using a bold font.
	bool isDefault;
	
	//: Offset from the content location.
	BPoint offset;		
};

#endif // GLYPH_MENU_ITEM_H