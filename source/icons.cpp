/***********************************************************************/
/*                                NOTICE                               */
/*                                ------                               */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/*                    This software was developed by                   */
/*                            3rd-Evolution                            */
/*                                                                     */
/* Any reproduction of this software in whole or in part must contain  */
/*                   this notice in its entirety.                      */
/*                                                                     */
/* 3rd-Evolution  is  providing this  software "as is"  and  makes no  */
/* warranty, express or  implied,  as  to  the  accuracy,  capability, */
/* efficiency,  merchantability,  or  functioning  of  this  software  */
/* and/or documentation. In no event will 3rd-evolution be liable for  */
/* any  general,  consequential,   indirect,  incidental,   exemplary, */
/* or special damages, even  if 3rd-evolution has been advised of the  */
/* possibility  of such damages,  irrespective  of  the cause of such  */
/* damages.  For short: 3rd-evolution is impeccable and so any damage  */
/* is your fault.                                                      */
/*                                                                     */
/* Permission  to use, copy, modify, and distribute this software for  */
/* any purpose and without  fee is hereby  granted. For  any comments, */
/* bugs or thanks, please email us: info@3rd-evolution.de              */
/*                                                                     */
/***********************************************************************/

#include "pch.h"
#include "icons.h"

// ==== globals ====

const float icon_width  = 23;
const float icon_height = 15;

// ==== icon_active_view ====

const int32 icon_active_view_size  = 1035;

unsigned char icon_active_view[] ={
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xFF,0xFF,0x66,0xFF,0xFF,0x66,
0xFF,0xFF,0x66,0xFF,0xFF,0x66,0xFF,0xFF,0x66,0xFF,0xFF,0x66,0xFF,0xFF,0x66,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0x60,0x60,0x60,0x60,0x60,0x60,0xFF,0xAF,0x13,
0xFF,0xAF,0x13,0xFF,0xAF,0x13,0xFF,0xAF,0x13,0xFF,0xAF,0x13,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x78,0x78,0x78,0x60,0x60,0x60,0x60,0x60,0x60,0xC0,0xC0,0xC0,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x60,0x60,0x60,0x60,0x60,0x60,0xB8,0xB8,0xB8,0xB8,0xB8,0xB8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,
0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,
0x60,0x60,0x60,0xB8,0xB8,0xB8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,0xC0,0xC0,0xC0,
0xB8,0xB8,0xB8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,0xC0,0xC0,0xC0,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,0x77,0x74,0x77,
0x60,0x60,0x60,0x60,0x60,0x60,0x98,0x98,0x98,0xC0,0xC0,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,0x77,0x74,0x77,0x60,0x60,0x60,
0x60,0x60,0x60,0x98,0x98,0x98,0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0xB8,0xB8,0xB8,
0x98,0x98,0x98,0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,
0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0xB8,0xB8,0xB8,0x78,0x78,0x78,
0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x60,0x60,0x60,0xB8,0xB8,0xB8,0xB8,0xB8,0xB8,0x78,0x78,0x78,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77};

// ==== icon_hidden_view ====

const int32 icon_hidden_view_size  = 1035;

unsigned char icon_hidden_view[] ={
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0x98,0x98,0x98,0x98,0x98,0x98,
0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,
0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x98,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x78,0x78,0x78,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x78,0x78,0x78,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77};

// ==== icon_visible_view ====

const int32 icon_visible_view_size  = 1035;

unsigned char icon_visible_view[] ={
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xFF,0xFF,0x66,0xFF,0xFF,0x66,
0xFF,0xFF,0x66,0xFF,0xFF,0x66,0xFF,0xFF,0x66,0xFF,0xFF,0x66,0xFF,0xFF,0x66,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xFF,0xAF,0x13,0xFF,0xAF,0x13,0xFF,0xAF,0x13,
0xFF,0xAF,0x13,0xFF,0xAF,0x13,0xFF,0xAF,0x13,0xFF,0xAF,0x13,0x78,0x78,0x78,0x78,0x78,0x78,
0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x78,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x78,0x78,0x78,0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,
0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,
0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x78,0x78,0x78,0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,
0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,
0xC8,0xC8,0xC8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xC8,0xC8,0x00,0x00,0x00,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x78,0x78,0x78,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,
0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0xC8,0x00,0x00,0x00,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77,
0x77,0x74,0x77,0x77,0x74,0x77,0x77,0x74,0x77};
