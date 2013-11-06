BeOS/Haiku LogoFramework to create Windows-style multidocument applications.

Under Windows all document windows of an application are contained in a top-level application window. This is called a multiple document interface (or MDI for short). Under BeOS the document windows are floating free on your desktop. You don't even know, which window belongs to which application. In Windows terminology this would be called a single document interface (SDI). (This isn't 100% true. SDI normally implies, that every window is displayed by a seperate process. This isn't true for BeOS applications.)

Both concepts are useful. Under Windows most webbrowsers use a BeOS like interface, but text processors and editors use the multiple document interface.

Under BeOS you didn't have an option. You can't add a window as a child to another window. And normal BViews can't be used to simulate windows, because they don't maintain a z-order.

But now the BeMDI framework brings MDI windows to the BeOS. It includes various classes, which work together to create the look and feel of a MDI interface.
