  /// \file BufferDevice.h
/*
 *
 * BufferDevice.h header template automatically generated by a class generator
 * Creation date : dim. janv. 17 2016
 *
 * This file is part of xdrstream libraries.
 * 
 * xdrstream is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * xdrstream is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with xdrstream.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef BUFFERDEVICE_H
#define BUFFERDEVICE_H

#include "xdrstream/IODevice.h"

namespace xdrstream
{

/** 
 *  @brief  BufferDevice class
 */ 
class BufferDevice : public IODevice 
{
public:
	/**
	 * @brief Constructor with initial buffer size in bytes
	 *        Open mode is set to write only
	 *
	 * @param  size the initial size of the buffer
	 */
	BufferDevice(xdr_size_t size = 1024);

	/**
	 * @brief Constructor with buffer and buffer size.
	 *
	 *        The third argument specifies whether the device should copy
	 *        the buffer pointer. Then a new buffer is allocated
	 *        and the buffer passed in argument is copied using memcpy().
	 *
	 *        The cursor position is set to 0 (start of buffer).
	 *        The buffer device is set to read only mode.
	 *
	 * @param  pBuffer the buffer pointer
	 * @param  size the buffer size
	 * @param  copy whether the buffer has to be copied
	 */
	BufferDevice(char *pBuffer, xdr_size_t size, bool copy = true);

	/**
	 *  @brief  Constructor with buffer and buffer size.
	 *
	 *         The fourth argument specifies whether the device should copy
	 *         the buffer pointer. Then a new buffer is allocated
	 *         and the buffer passed in argument is copied using memcpy().
	 *
	 *         Open modes can be :
	 *          - XDR_READ    : User can read but not write in the buffer.
	 *                          The initial cursor position is set to 0, ready
	 *                          to read the first bytes
	 *          - XDR_WRITE   : User can write into the buffer but can't
	 *                          read it. The initial cursor position is set to
	 *                          'size', ready to append new bytes
	 *          - XDR_APPEND  : User can read and write into the buffer.
	 *                          The cursor is set to 'size', ready to append
	 *                          bytes after the last written bytes
	 *
	 *          An exception is thrown if XDR_NOT_OPENED is passed
	 *
	 *  @param  pBuffer the buffer pointer
	 *  @param  size the buffer size
	 *  @param  copy whether the device has to copy the buffer
	 */
	BufferDevice(OpenMode openMode, char *pBuffer, xdr_size_t size, bool copy = true);

	/**
	 *  @brief Destructor
	 */
	virtual ~BufferDevice();

public:
	//******************/
	//*   Buffer API   */
	//******************/
	/**
	 *  @brief  Set a new buffer and its size.
	 *
	 *  @param  pBuffer the buffer pointer
	 *  @param  size the buffer size
	 *  @param  copy whether the device has to copy the new buffer
	 */
	Status setBuffer(char *pBuffer, xdr_size_t size, bool copy = true);

	/**
	 *  @brief  Set the device buffer ownership
	 *
	 *  @param  owner whether the device owns the current buffer
	 */
	void setOwner(bool owner = true);

	/**
	 *  @brief  Get the buffer pointer
	 */
	char *getBuffer();

	/**
	 *  @brief  Get the buffer pointer
	 */
	const char *getBuffer() const;

	/**
	 *  @brief  Get the buffer size
	 */
	xdr_size_t getBufferSize() const;

	/**
	 *  @brief  Set the expansion size of the buffer. This is the
	 *          number of bytes that are added when user try to write
	 *          in the buffer with not enough space.
	 *
	 *  @param  size the expand size
	 */
	void setExpandSize(xdr_size_t size);

	/**
	 *  @brief  Get the expand size
	 */
	xdr_size_t getExpandSize() const;

	/**
	 *  @brief  Expand the buffer by adding n bytes
	 */
	Status expandBuffer(xdr_size_t size = 0);

	/**
	 *  @brief  Reset the device
	 */
	Status reset();

	/**
	 *  @brief  Whether the device is readable
	 */
	bool isReadable() const;

	/**
	 *  @brief  Whether the device is writable
	 */
	bool isWritable() const;

	/**
	 *  @brief  Get the buffer size. Alias for getBufferSize();
	 */
	xdr_size_t size() const;

	/**
	 *  @brief  Get the cursor position in the buffer
	 */
	xdr_size_t getPosition() const;

	/**
	 *  @brief  Seek the cursor in the device at the specified location
	 *
	 *  @param  position the position to point in the device
	 */
	Status seek(xdr_size_t position);

public:
	//**************/
	//*   IO API   */
	//**************/
	/**
	 *  @brief  Read a single value (int, float, ...)
	 *
	 *  @param  pAddress the address of the single value to read
	 *  @param  dataSize the size of the single value in memory (use sizeof(val))
	 */
	Status readData(void *pAddress, xdr_size_t dataSize);

	/**
	 *  @brief  Read a c-string array from the device.
	 *          An array of size strLen+1 is allocated using new operator
	 *          and the last character of the string is set to '\0' null character.
	 *          To write a c-string into the device, use writeArray(pCString, strLen)
	 *
	 *  @param  pCString the address of the c-string to read
	 *  @param  strLen the length of the c-string (strLen+1 with '\0' char at the end)
	 */
	Status readCString(char *&pCString, xdr_size_t &strLen);

	/**
	 *  @brief  Read a fixed size data array.
	 *          The array has to be allocate before calling this function
	 *
	 *  @param  pAddress the address of the array
	 *  @param  arraySize the number of element to read in the array
	 *  @param  elementSize the size in memory of a single element
	 */
	Status readStaticArray(void *pAddress, xdr_size_t arraySize, xdr_size_t elementSize);

	/**
	 *  @brief  Read a fixed size data array.
	 *          The array is allocate in this function using new operator.
	 *          The array size is read from the device and returned by reference.
	 *
	 *  @param  pAddress the address of the array to receive
	 *  @param  arraySize the number of element read from the device (returned by reference)
	 *  @param  elementSize the size in memory of a single element
	 *  @param  allocator the allocator function that will perform the memory allocation for the array
	 */
	Status readDynamicArray(void *&pAddress, xdr_size_t &arraySize, xdr_size_t elementSize, xdr_allocator allocator);

	/**
	 *  @brief  Write a single value (int, float, ...)
	 *
	 *  @param  pAddress the address of the single value to write
	 *  @param  dataSize the of the single calue in memory (use sizeof(val))
	 */
	Status writeData(const void *pAddress, xdr_size_t dataSize);

	/**
	 *  @brief  Write array in the device
	 *
	 *  @param  pAddress the address of the array to write
	 *  @param  arraySize the number of element to write in the device
	 *  @param  elementSize the size of a single element in memory (use sizeof(val))
	 */
	Status writeArray(const void *pAddress, xdr_size_t arraySize, xdr_size_t elementSize);

	/**
	 *  @brief  Write n empty bytes in the device
	 *          In read mode, just skip bytes using seek(current + nBytes)
	 *
	 *  @param  nBytes the number of empty bytes to write in the device
	 */
	Status writeEmptyBytes(xdr_size_t nBytes);

private:
	/**
	 *  @brief  Read/write the record header in the device
	 *
	 *  @param  mode the streaming mode (read or write)
	 *  @param  recordHeader the record header to read/write
	 */
	Status recordHeader(StreamingMode mode, Header &recordHeader);

	/**
	 *  @brief  Read/write the block header in the device
	 *
	 *  @param  mode the streaming mode (read or write)
	 *  @param  blockHeader the block header to read/write
	 */
	Status blockHeader(StreamingMode mode, Header &blockHeader);

	// buffer always opened ...
	inline bool isOpened() const { return true; }

protected:
	char                    *m_pBuffer;               ///< The main buffer
	char                    *m_pBufferPosition;       ///< The current position in the buffer
	xdr_size_t               m_bufferSize;            ///< The whole buffer size
	xdr_size_t               m_expandSize;            ///< The expand size on buffer re-allocation
	bool                     m_isOwner;               ///< Whether the device owns the buffer
	OpenMode                 m_openMode;              ///< The buffer device open mode
}; 

} 

#endif  //  BUFFERDEVICE_H
