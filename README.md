# DisplayDrivers-Linux
* Research, Interfacing LDC Controller (LCDC) applications for pixelated displays for Libhal
* Essentially what this should be doing is taking in a generic type of buffer and knowing how to manage this buffer in memory \
depending on the type of formatting that is given from the user.


### API Design Discussion Topics
* There are various approaches to this regarding how this buffer is going to work
* Including what are different trades that are happening and how they effect in cost.
* This is a few approaches in looking how buffers are going to be managed, and what types of data do we know should the buffer manage
* While also including what other things that the user calling these API's without having to specify specific things.
* Where we know that some type of data we are going to want to somehow manage are the position (coordinates), and pixel value (rgba)
    * An approach is potentially having a buffer containing {pos, rgba}
    * One other approach is splitting from the buffer and pixel data seperately.


### Buffer management
* User interaction with buffered data
* How different displays are going to handle this data
* Since displays have different formats, this means the data in a buffer is going to be put into memory different.
* Seeing the cost when you are trying to have pixel data class and the buffer class seperate.


### Resources

Resources for setting and describing the LDC controller (LCDC) for SH7722 and SH7731 \
`https://www.renesas.com/us/en/document/apn/sh7722sh7731-group-lcd-controller-setup-example`

Link for interfaces in LCD Display modules – SPI, I2C, LVDS, MIPI, VX1, EDP and others \
`https://riverdi.com/blog/interfaces-in-lcd-display-modules-spi-i2c-lvds-mipi-vx1-edp-and-others#SPI_Serial_Peripheral_Interface`

### Links to Pixelated LCD displays
Link to the adafruit Bright White LED Matrix \
`https://www.adafruit.com/product/1613?gad_source=1`






