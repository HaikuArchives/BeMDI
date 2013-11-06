/***********************************************************************/
/* pch.h                                                               */
/*                                                                     */
/* Precompiled header. Included by every source file.                  */
/*                                                                     */
/*               Copyright 2000, www.3rd-evolution.de                  */
/*                                                                     */
/* Author : Thomas Krammer                                             */
/*                                                                     */
/* For any comments, bugs or thanks, please email us.                  */
/* Email :   info@3rd-evolution.de                                     */
/*                                                                     */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include <kernel/OS.h>
#include <kernel/image.h>
#include <kernel/scheduler.h>
#include <kernel/fs_attr.h>

#include <app/Application.h>
#include <app/MessageRunner.h>
#include <app/Messenger.h>
#include <app/MessageFilter.h>

#include <storage/File.h>
#include <storage/Path.h>
#include <storage/AppFileInfo.h>
#include <storage/FindDirectory.h>
#include <storage/FilePanel.h>
#include <storage/Volume.h>

#include <interface/View.h>
#include <interface/Window.h>
#include <interface/Box.h>
#include <interface/TabView.h>
#include <interface/ListView.h>
#include <interface/Bitmap.h>
#include <interface/Button.h>
#include <interface/Menu.h>
#include <interface/MenuBar.h>
#include <interface/PopUpMenu.h>
#include <interface/MenuItem.h>
#include <interface/ScrollView.h>
#include <interface/Alert.h>
#include <interface/Screen.h>
#include <interface/StringView.h>
#include <interface/TextView.h>
#include <interface/TextControl.h>
#include <interface/PictureButton.h>
#include <interface/Region.h>
#include <interface/CheckBox.h>
#include <interface/Dragger.h>

#include <translation/BitmapStream.h>
#include <translation/TranslatorRoster.h>

#include <be_apps/Deskbar/Deskbar.h>

#include <support/Beep.h>
#include <support/Autolock.h>
#include <support/String.h>
#include <support/StopWatch.h>

#include <utility>
#include <string>
#include <vector>
#include <algorithm>
