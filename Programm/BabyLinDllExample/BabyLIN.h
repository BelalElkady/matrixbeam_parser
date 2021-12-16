#ifndef BABYLIN_OLD_H
#define BABYLIN_OLD_H

#include "BabyLINReturncodes.h"

/** \addtogroup l_structures
 *  \brief List of legacy BabyLIN structures
 *
 *  The following structures are used to retrieve data from a running BabyLIN
 * device like frame- and signal-reports or error and debug information
 *  Most of the structures are outdated and no longer used for the new BabyLIN
 * API
 *  @{
 */

/** @brief Carries information about one signal.
 * @deprecated
 */
typedef struct _BL_signal_t {
  // ! Index number of signal; see the SDF for the adequate number
  unsigned char index;
  // ! Defines wether this signal is a normal, value-based one (0) or LIN2.0
  // array signal (1).
  int isArray;
  // ! Value of the signal.
  unsigned short value;
  // ! Length of the array.
  int arrayLength;
  // ! Value(s) of the signal, if isArray == 1.
  unsigned char array[8];
} BL_signal_t;

// ! Return data of the command 'targetid'
typedef struct _BL_targetid_t {
  /** \brief Type of the hardware
   *
   * | Value | Device |
   * |------:|--------|
   * |0x100  |Baby-LIN|
   * |0x101  |Baby-LIN-PLUS|
   * |0x102  |Baby-LIN-RC|
   * |0x103  |Baby-LIN-KS01|
   * |0x200  |Baby-LIN-RM|
   * |0x300  |HARP|
   * |0x400  |Baby-LIN-RC-PLUS|
   * |0x500  |Baby-LIN-RMII|
   * |0x502  |HARP-4|
   * */
  unsigned short type;

  // ! Software version
  unsigned short version;

  // ! Software build number
  unsigned short build;

  /** \brief Software related flags
   *
   * |Value|Description|
   * |----:|:----------|
   * |0x01 |Testversion|
   * */
  unsigned short flags;

  // ! Device's serial number
  long serial;

  // ! Remaining heap size on device (memory available for SDF dowload)
  long heapsize;

  // ! Reserved value (ignore for now)
  long spare;

  // ! Textual name of the device (zero-terminated C-string)
  char name[128];
} BL_targetid_t;

// ! Represents a LIN error message
typedef struct _BL_error_t {
  /** \brief Time of occurence (usec, since first start of LIN activity).
   *
   *
   * */
  unsigned long timestamp;
  /** \brief Error type
   *
   * | Value | Name | Description | Status |
   * |------:|:-----|:------------|:-------|
   * |1|ERRTYPE_ID|Parity error in ID| |
   * |2|ERRTYPE_DATA|Read data from BUS does not match send data| Frame-ID |
   * |3|ERRTYPE_FRAMING|Framing error in data reception|Frame-ID|
   * |4|ERRTYPE_CHECKSUM|Checksum failed|Frame-ID|
   * |5|ERRTYPE_DATATO|Data timed out (incomplete msg reception)|Frame-ID|
   * |6|ERRTYPE_SEQ|Unexpected state sequencing|internal status|
   * |8|ERRTYPE_MACRO|Error in macro execution|internal status|
   * |9|ERRTYPE_BUSBUSY|Bus is already used|internal status|
   * |10|ERRTYPE_BUSOFF|Bus is offline (no bus power) |internal status|
   * |11|ERRTYPE_BUSSPEED_DIFFERS|Actual bus-speed differs from LDF bus speed
   * (Warning) |actual speed|
   * |12|ERRTYPE_KWP_ERROR|Error in KWP|KWP error code|
   * |13|ERRTYPE_APPLICATION|Application error|unused|
   * */
  unsigned short type;
  /** \brief Additional error information
   *
   * See @ref type descriptions for detailed Information
   * */
  unsigned short status;
} BL_error_t;

// ! Carries information about one frame
typedef struct _BL_frame_t {
  // ! Set to != 0 if timing information present.
  unsigned char extended;

  /** \brief Additional, informational flags
   *
   * Used as a bitfield, multiple flags possible
   * | Value | Description |
   * |------:|:------------|
   * | 0x01  |Valid CLASSIC checksum (V1)|
   * | 0x02  |Valid EXTENDED checksum (V2)|
   * | 0x04  |incomplete frame without checksum, not an error|
   * | 0x08  |Errorframe (f.ex: no data)|
   * | 0x10  |Frame is slaveresponse to a master request. If set, the upper 3
   * bits of flags denote a master request id|
   * | 0x20  |Event triggered frame ( only if 0x10 is not set )|
   * */
  unsigned char flags;

  // ! Global time index of frame transmission start (in us).
  unsigned long timestamp;

  // ! Duration of BREAK (us, only if extended != 0).
  unsigned short breaklength;

  // ! Time between BREAK-end and SYNC-end (us, only if extended != 0).
  unsigned short synctime;

  // ! Length of frame (including ID byte, data bytes and checksum byte). If ==
  // 1, only the ID byte is existant (i.e. unresponded SlaveResp)!
  unsigned char length;

  // ! Transmitted data, LSB first, up to length tuples.
  /** First value is the frame's ID (or SDF-number, if extended == 0), followed
   *  by the data bytes; the last value-time tuple is the checksum byte.
   *
   *  The times are measured from the end of the previous data byte to the
   *  end of the current byte (all in us, timing information only valid if
   *  extended != 0):
   *
   *
   */
  struct {
    unsigned char value;
    unsigned short time;
  } framedata[10];

  /**
   * @brief no longer used
   * @deprecated no longer used
   */
  unsigned short status;
} BL_frame_t;

// ! Carries information about DTL protocol (both requests and responses).
typedef struct _BL_dtl_t {
  // ! Status of protocol frame see BL_DTL_STATUS for details
  BL_DTL_STATUS status;

  // ! NAD of protocol frame
  unsigned char nad;

  // ! Length of the data-array.
  int length;
  // ! frame data, beginning with the (R)SID.
  unsigned char data[4 * 1024];
} BL_dtl_t;

/** \brief Information about a BabyLIN port on the host operating system
 *
 * The structure holds information about a BabyLIN device connected to the PC
 *
 * Use @ref BL_searchBabyLinPorts to retrieve a list of connected
 * BabyLIN-Devices
 *
 * */
typedef struct _BL_portInfo_t {
  /** the COM-port number the device is connected to (windows only), use this
   * value for BLC_open */
  int portNr;
  /** the type of interface of the connected device (0=USB) */
  int type;
  /** the name of the connected device (f.ex. BabyLIN RM-II) */
  char name[256];
  /** the linux device file the BabyLIN is connected to (linux only) */
  char device[256];
} BL_portInfo_t;

/** @}*/

#if defined(__cplusplus)
#include <cstddef>  // get "size_t", used by function BL_encodeSignal())
extern "C" {
#else
#include <stddef.h>  // get "size_t", used by function BL_encodeSignal())
#endif

/** \addtogroup l_connection_handling Legacy Connection Handling
 *  \brief List of legacy BabyLIN connection handling function
 *
 *  The following functions are used to setup a connection to a BabyLIN device.
 *
 *  These functions are outdated and no longer used for the new BabyLIN API.
 *  @{
 */

// ! Returns number of available Baby-LIN devices.
/**
 *  \param pdest       pointer to BLC_portInfo_t array, where the infos about
 * the recognized Baby-LIN's will be supplied.
 *                     If this pointer is given with NULL, the function will
 * only return the count of available devices.
 *  \param psize       pointer to interger which holds the maximum count of
 * entries, which may be filled by the function into the array pdest.
 *                     If this pointer is given with NULL, the function will
 * only return the count of available devices.
 *  \return            Returns number of available Baby-LIN devices.
 */
int BL_DLLIMPORT BL_searchBabyLinPorts(BL_portInfo_t *pdest, int *psize);

int BL_DLLIMPORT BL_searchBabyLIN(int port);

// ! Get the major and minor version number of the library
/**
 *  This function enters the version in the given parameter variables of the
 *  library.
 *  \param major    major part of version number.
 *  \param minor    minor part of version number.
 */
void BL_DLLIMPORT BL_getVersion(int *major, int *minor);

// ! Get the version string of the library
/**
 *  This function returns the version string of the library.
 *  \return         returns a C-string with the version information.
 */
CPCHAR BL_DLLIMPORT BL_getVersionString(void);

// ! Open a connection to a BabyLIN device.
/**
 *  This function tries to open the designated port and to start communication
 *  with the device.
 *  \param port     represents the port number; it uses Windows-style numbering,
 *                  which means it starts with '1' for the first serial port.
 *                  '0' is reserved.
 *  \return         Returns an handle for the designated connection; on failure
 *                  NULL. You may fetch the corresponding (textual) error (for
 *                  return values < -1000) with  BL_getLastError().
 */
#if defined(_WIN32)
BL_HANDLE BL_DLLIMPORT BL_open(unsigned int port);
#else
BL_HANDLE BL_DLLIMPORT BL_open(const char *port);
#endif

// ! Close connection to Device.
/** BL_close() closes an open connection, given by handle.
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open.
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation  BL_getLastError.
 */
int BL_DLLIMPORT BL_close(BL_HANDLE handle);

// ! Close ALL connections to ALL Devices.
/** closeAllDevices() closes all open connection; all handles are invalidated.
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation  BL_getLastError().
 */
int BL_DLLIMPORT BL_closeAll(void);

// ! Resets the BabyLIN device to an consistent and deactivated state.
/** Afterwards, the device will no longer monitor the bus, neither acting as
 * slave
 *  nor as master.
 *  \param handle   Handle representing the connection; returned previously by
 *                   BL_open().
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_flush(BL_HANDLE handle);

// ! Requests the information about the target
/**
 *  \param handle    Handle representing the connection; returned previously by
 *                    connectDevice().
 *  \param targetID  pointer to BL_targetid_t structure to hold the information
 *                   after the successful call, has to be allocated.
 *  \return          Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000)
 * getLastDeviceError().
 */
int BL_DLLIMPORT BL_getTargetID(BL_HANDLE handle, BL_targetid_t *targetID);

// ! Loads the specified SDF-file into library and optionally the BabyLIN
// device.
/** The SDF could be generated by LINWorks/SessionConf from a LDF file.
 *  WARNING: this resets the device upon download!
 *  \param handle     Handle representing the connection; returned previously by
 *                    BL_open().
 *  \param filename   C-string with the (fully qualified) filename (i.e.
 * "mybus.sdf", if
 *                    in the same directory, or "c:/data/mybus.sdf").
 *  \param download   boolean value, determines if the SDF profile gets
 * downloaded into
 *                    the BabyLIN device (!=0) or only used in the library (=0).
 *  \return           Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_loadSDF(BL_HANDLE handle, const char *filename, int download);

// ! Loads the already loaded SDF-file into the BabyLIN device.
/** The SDF could be generated by LINWorks/SessionConf from a LDF file and must
 * have been
 *  loaded previously by an BL_loadSDF() command.
 *  WARNING: this resets the device!
 *  \param handle     Handle representing the connection; returned previously by
 *                    BL_open().
 *  \return           Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_downloadSDF(BL_HANDLE handle);

// ! Returns a C-string with the textual representation of the last error.
/**
 *  The string returned is a pointer to an internal variable; don't ever try
 *  to free it! The errors are described in English.
 *  Note however, only Errorcodes < -1000 get described - all other return
 *  values are directly sent by the device. Values >0 usually denote the index
 *  of the wrong parameter of a command. Values <0 define other errors like
 *  'out of memory' and alike. Consult the BabyLIN documentation for further
 *  reference.
 *  \param handle   Handle to the erroneous connection.
 *  \return         C-String with textual description of last error.
 */
CPCHAR BL_DLLIMPORT BL_getLastError(BL_HANDLE handle);

/** @}*/

/** \addtogroup l_sdf_handling
 *  \brief List of legacy functions to get information about the loaded SDF
 *
 *  The following functions are used to retrieve information about the elements
 * in a loaded SDF-file.
 *  These functions are outdated and no longer used for the new BabyLIN API.
 *  @{
 */

// ! Returns the number of node entries.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \return            Number of nodes set by lnode message.
 */
int BL_DLLIMPORT BL_getNodeCount(BL_HANDLE handle);

// ! Returns the name of given node entry.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param idx         Zero based index of requested node entry.
 *  \param dstbuf      Pointer to char array which gets filled (must hold min.
 * 'buflen' bytes).
 *  \param buflen      How many bytes should get returned.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 */
int BL_DLLIMPORT BL_getNodeName(BL_HANDLE handle, int idx, char *dstbuf, int buflen);

// ! Returns the number of frame entries.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \return            Number of frames set by lframe message.
 */
int BL_DLLIMPORT BL_getFrameCount(BL_HANDLE handle);

// ! Returns the name of given frame entry.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param idx         Zero based index of requested frame entry.
 *  \param dstbuf      Pointer to char array which gets filled (must hold min.
 * 'buflen' bytes).
 *  \param buflen      How many bytes should get returned.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 */
int BL_DLLIMPORT BL_getFrameName(BL_HANDLE handle, int idx, char *dstbuf, int buflen);

// ! Returns the number of signal entries.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \return            Number of signals set by lsignal message.
 */
int BL_DLLIMPORT BL_getSignalCount(BL_HANDLE handle);

// ! Returns the name of given signal entry.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param idx         Zero based index of requested signal entry.
 *  \param dstbuf      Pointer to char array which gets filled (must hold min.
 * 'buflen' bytes).
 *  \param buflen      How many bytes should get returned.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 */
int BL_DLLIMPORT BL_getSignalName(BL_HANDLE handle, int idx, char *dstbuf, int buflen);

// ! Returns the number of signal entries in Frame idx.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param idx         Zero based index of requested frame entry.
 *  \return            Number of signals set by lsignal message.
 */
int BL_DLLIMPORT BL_getSignalsInFrameCount(BL_HANDLE handle, int idx);

int BL_DLLIMPORT BL_getSignalInFrame(BL_HANDLE handle, int frameIndex, int signalIndex);

int BL_DLLIMPORT BL_getFrameNrForFrameId(BL_HANDLE handle, unsigned char frameId);

/** @}*/

/** \addtogroup l_callback_handling Legacy Callback Handling
 *  \brief List of legacy functions to manage callback functions
 *
 *  The following functions are used to register callback functions for a
 * BabyLIN connection.
 *  A callback will be called whenever a corresponding message is recieved on
 * the connection it is registered to ( push method ).
 *  If you want to use a pull method to retrieve the data, have a look at the
 * \ref l_pull_handling section of the documentation
 *  These functions are outdated and no longer used for the new BabyLIN API.
 *  @{
 */

// ! callback function header whenever a frame report is received from a BabyLIN
// device
typedef void(BL_frame_callback_func)(BL_frame_t frame);
// ! callback function header whenever a signal report is received from a
// BabyLIN device
typedef void(BL_signal_callback_func)(BL_signal_t signal);
// ! callback function header whenever a buserror report is received from a
// BabyLIN device
typedef void(BL_buserror_callback_func)(BL_error_t error);
// ! callback function header whenever a debug message is received from a
// BabyLIN device
typedef void(BL_debug_callback_func)(const char *text);
// ! callback function header whenever a dtl request is received from a BabyLIN
// device
typedef void(BL_dtl_request_callback_func)(BL_dtl_t frame);
// ! callback function header whenever a dtl response is received from a BabyLIN
// device
typedef void(BL_dtl_response_callback_func)(BL_dtl_t frame);

// ! Registers a callback function, which is called on every reception of a
// (monitored) frame.
/** Issuing a NULL-pointer de-registers the callback function. As the function
 * is called
 *  from another thread context, take care of thread-safety (i.e. using mutexes,
 * etc.).
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param callback    Pointer to a function call-compatible to
 * BL_frame_callback_func.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_registerFrameCallback(BL_HANDLE handle, BL_frame_callback_func *callback);

// ! Registers a callback function, which is called on every reception of a
// (monitored) signal.
/** Issuing a NULL-pointer de-registers the callback function. As the function
 * is called
 *  from another thread context, take care of thread-safety (i.e. using mutexes,
 * etc.).
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param callback    Pointer to a function call-compatible to
 * BL_signal_callback_func.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_registerSignalCallback(BL_HANDLE handle, BL_signal_callback_func *callback);

// ! Registers a callback function, which is called on every reception of a bus
// error.
/** Issuing a NULL-pointer de-registers the callback function. As the function
 * is called
 *  from another thread context, take care of thread-safety (i.e. using mutexes,
 * etc.).
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param callback    Pointer to a function call-compatible to
 * BL_frame_buserror_func.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_registerBusErrorCallback(BL_HANDLE handle,
                                             BL_buserror_callback_func *callback);  // for backwards compatibility

// ! Registers a callback function, which is called on every reception of a
// debug message.
/** Issuing a NULL-pointer de-registers the callback function. As the function
 * is called
 *  from another thread context, take care of thread-safety (i.e. using mutexes,
 * etc.).
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param callback    Pointer to a function call-compatible to
 * BL_debug_callback_func.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_registerDebugCallback(BL_HANDLE handle, BL_debug_callback_func *callback);

// ! Registers a callback function, which is called on every reception of a DTL
// request, but only if at least one Slave is emulated.
/** Issuing a NULL-pointer de-registers the callback function. As the function
 * is called
 *  from another thread context, take care of thread-safety (i.e. using mutexes,
 * etc.).
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param callback    Pointer to a function call-compatible to
 * BL_dtl_request_callback_func.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_registerDTLRequestCallback(BL_HANDLE handle, BL_dtl_request_callback_func *callback);

// ! Registers a callback function, which is called on every reception of a DTL
// response, but only if BabyLIN emulates the master node.
/** Issuing a NULL-pointer de-registers the callback function. As the function
 * is called
 *  from another thread context, take care of thread-safety (i.e. using mutexes,
 * etc.).
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param callback    Pointer to a function call-compatible to
 * BL_dtl_response_callback_func.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_registerDTLResponseCallback(BL_HANDLE handle, BL_dtl_response_callback_func *callback);

/** @}*/

/** \addtogroup l_commands
 *  \brief List of legacy functions to send commands to a BabyLIN device
 *
 *  The following functions are used to send commands to a BabyLIN device to set
 * or retrieve simulation or device parameters.
 *  These functions are outdated and no longer used for the new BabyLIN API.
 *  @{
 */

// ! Sends the (textual) specified command to the BabyLIN device.
/** The command must match the command syntax as specified in the BabyLIN
 *  documentation. The trailing ';' may be omitted; but you may not specify
 *  several commands at once!
 *  \param handle   Handle representing the connection; returned previously by
 *                  getDeviceHandle().
 *  \param command  C-string with @ref Commands (i.e. "status;")
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * getLastDeviceError().
 */
int BL_DLLIMPORT BL_sendCommand(BL_HANDLE handle, const char *command);

// ! Sends the (textual) specified command to the BabyLIN device. Data response
// requested.
/** The command must match the command syntax as specified in the BabyLIN
 *  documentation. The trailing ';' may be omitted; but you may not specify
 *  several commands at once!
 *  The content of '*length' will be set to really received number of data
 bytes.
 *  If one of the required pointers 'data' or 'length' is NULL or the buffer
 size is too small,
 *  the function returns the needed minimum buffer length in '*length' (if this
 pointer is valid).

 *  \param handle   Handle representing the connection; returned previously by
 *                   BL_open().
 *  \param command  C-string with @ref Commands (i.e. "status;")
 *  \param data     Pointer to data save location (destination buffer)
 *  \param length   Pointer to requested data length.
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 BL_getLastError().
 */
int BL_DLLIMPORT BL_sendCommandD(BL_HANDLE handle, const char *command, char *data, int *length);

// ! Sends the (textual) specified command to the BabyLIN device with the
// ability to insert specific parameters.
/** The command must match the command syntax as specified in the BabyLIN
 *  documentation. The trailing ';' may be omitted; but you may not specify
 *  several commands at once!
 *  This function works similiar to functions like 'printf'. You may specify
 *  placeholders, whose value get specified as parameter to the function.
 *
 *  Possible placeholders are:
 *
 *    %S    insert signal number for name specified as parameter
 *    %F    insert frame number for name specified as parameter
 *    %M    insert macro number for name specified as parameter
 *
 *  Examples:
 *
 *    BL_sendCommandF(handle, "setsig %S 1;", "signal name");
 *    BL_sendCommandF(handle, "disframe %F;", "frame name");
 *    BL_sendCommandF(handle, "macro_exec %M;", "macro name");
 *
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param command  C-string with @ref Commands and placeholders (i.e. "setsig %S
 * 1;").
 *  \param ...      additional parameters, as specified by placeholders.
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_sendCommandF(BL_HANDLE handle, const char *command, ...);

// ! Sends the (textual) specified command to the BabyLIN device with the
// ability to insert specific parameters.
/** The command must match the command syntax as specified in the BabyLIN
 *  documentation. The trailing ';' may be omitted; but you may not specify
 *  several commands at once!
 *  This function works similiar to functions like 'printf'. You may specify
 *  placeholders, whose value get specified as parameter to the function.
 *
 *  Possible placeholders are:
 *
 *    %S    insert signal number for name specified as parameter
 *    %F    insert frame number for name specified as parameter
 *    %M    insert macro number for name specified as parameter
 *
 *  Examples:
 *
 *    BL_sendCommandFs(handle, "setsig %S 1;", "signal name");
 *    BL_sendCommandFs(handle, "disframe %F;", "frame name");
 *    BL_sendCommandFs(handle, "macro_exec %M;", "macro name");
 *
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param command  C-string with @ref Commands and placeholders (i.e. "setsig %S
 * 1;").
 *  \param name     name of signal, frame or macro
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_sendCommandFs(BL_HANDLE handle, const char *command, const char *name);

int BL_DLLIMPORT BL_mon_set(BL_HANDLE handle, int frameid, const int *databytes, int len);
int BL_DLLIMPORT BL_mon_xmit(BL_HANDLE handle, int frameId, int slottime);
int BL_DLLIMPORT BL_mon_set_xmit(BL_HANDLE handle, int frameId, const int *databytes, int len, int slottime);

// ! Sends the (raw!) command to the BabyLIN device.
/** The command must be encoded in the binary DP-Message format of BabyLIN.
 *  \param handle   Handle representing the connection; returned previously by
 *                   BL_open().
 *  \param command  char*-Buffer with the designated @ref Commands.
 *  \param length   length of buffer; gets set to actual sent command's length.
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_sendRaw(BL_HANDLE handle, const unsigned char *command, unsigned int *length);

// ! Sets the Diagnostic Transport Layer mode.
/**
 *  There are different Diagnostic modes, which offer different levels of
 * protocol functionality.
 *  The Baby-LIN will start with Diagnostic OFF on Power Up.
 *  If the BabyLIN acts as LIN master then the selection of an Diagnostic Mode
 * happens trough the usage
 *  of the appropriate API function calls. So the API functions
 * BL_sendRawMasterRequest or BL_sendRawSlaveResponse
 *  will start  the Diagnostic RAW mode, where as the API calls
 * BL_sendDTLRequest or BL_sendDTLResponse will start the
 *  Diagnostic DTL mode.
 *  If the BabyLIN acts as LIN slave then the DTL mode must be set by use of
 * this function.
 *  It is not possible to use different Diagnostics modes at the same time !
 *
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param mode        DTL mode:
 *                     0 = DTL_NONE = no DTL Support
 *                     1 = DTL_RAW = RAW Mode DTL Support
 *                     2 = DTL_COOKED = Cooked Mode DTL Support
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_setDTLMode(BL_HANDLE handle, int mode);

// ! Sends the given DTL MasterReq to the node identified by 'nad'.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param nad         NAD of the node the request gets send to.
 *  \param length      Length of the following data array.
 *  \param data        DTL frame data (begins with SID, followed by up to 4095
 * data bytes).
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_sendDTLRequest(BL_HANDLE handle, unsigned char nad, int length, unsigned char *data);

// ! Sends the given DTL SlaveResp for the node identified by 'nad'.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param nad         NAD of the node the response gets send for.
 *  \param length      Length of the following data array.
 *  \param data        DTL frame data (begins with RSID, followed by up to 4095
 * data bytes).
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_sendDTLResponse(BL_HANDLE handle, unsigned char nad, int length, unsigned char *data);

// ! Sends the given (non-DTL) SlaveResp upon receive of matching MasterReq with
// the specified as data (in as many frames as needed).
/**
 *  Upon the reveive of the next MasterReq frame, the every bit of the requestis
 * compared to
 *  'reqdata' if the corresponding bit of 'reqmask' is set (1). If all match,
 * Baby-LIN starts
 *  to send out the data given in 'data', 8 bytes with each SlaveResp frame.
 *
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param reqdata     Data of the expected MasterReq (exactly 8 bytes).
 *  \param reqmask     Mask for 'reqdata' to indicate which bits must match
 * (exactly 8 bytes).
 *  \param data        MasterReq frame data (multiple of 8 bytes).
 *  \param length         Length of data to send.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_sendRawSlaveResponse(BL_HANDLE handle, unsigned char *reqdata, unsigned char *reqmask,
                                         unsigned char *data, int length);

// ! Sends the given (non-DTL) MasterReq with the specified 8 bytes as data.
/**
 *  The internal raw-SlaveResponse-buffer is being reset and the Baby-LIN device
 * gets
 *  instructed to report the next 'count' SlaveResp-frames which in turn are
 * accumulated
 *  into the SlaveResponse-buffer which can be queried by
 * BL_getRawSlaveResponse().
 *
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param data        MasterReq frame data (exactly 8 bytes).
 *  \param count       Number of expected SlaveResp frames.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_sendRawMasterRequest(BL_HANDLE handle, unsigned char *data, int count);

// ! Returns the status of the last request-send operation.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \return            Status of last request operation if >= 0; see
 * BL_DTL_STATUS for
 *                     values. For < 0, see standard return values for error, or
 * for
 *                     textual representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getDTLRequestStatus(BL_HANDLE handle);

// ! Returns the status of the last request-send operation.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \return            Status of last request operation if >= 0; see
 * BL_DTL_STATUS for
 *                     values. For < 0, see standard return values for error, or
 * for
 *                     textual representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getDTLResponseStatus(BL_HANDLE handle);

// ! Returns the first 'length' bytes of the current SlaveResp-buffer.
/**
 *  The internal raw-SlaveResponse-buffer is filled continuously with the data
 * bytes of
 *  reported SlaveResp-frames and is being reset upon every call of
 * BL_sendRawMasterRequest().
 *
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param data        Pointer to char array which gets filled (must hold min.
 * 'length' bytes).
 *  \param length      How many bytes should get returned.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getRawSlaveResponse(BL_HANDLE handle, unsigned char *data, int length);
int BL_DLLIMPORT BL_updRawSlaveResponse(BL_HANDLE handle);

// ! Returns BL_OK if the last answer to a command contained additional data.
/** If there is no additional data present it returns BL_NO_ANSWER_DATA.
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_lastAnswerHasData(BL_HANDLE handle);

// ! If the last answer to a command contained additional data, then this
// function reports
// ! the type and size for a specific answer data set. Data set selected by
// name.
/** The following types of data sets are possible:
 *      BL_ANSWER_TYPE_INT - 32bit integer
 *      BL_ANSWER_TYPE_STR - zero-terminated string (variable length)
 *      BL_ANSWER_TYPE_BIN - binary data (variable length)
 *
 *  \param handle   Handle representing the connection; returned previously by
 *                   BL_open().
 *  \param name     char*-string with the name of answer data set
 *  \param type     type of data set is returned within
 *  \param length   length of data set is returned within
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getAnswerTypeByName(BL_HANDLE handle, const char *name, BL_ANSWER_TYPE *type, size_t *length);

// ! If the last answer to a command contained additional data, then this
// function reports
// ! the type and size for a specific answer data set. Data set selected by
// index.
/** The following types of data sets are possible:
 *      BL_ANSWER_TYPE_INT - 32bit integer
 *      BL_ANSWER_TYPE_STR - zero-terminated string (variable length)
 *      BL_ANSWER_TYPE_BIN - binary data (variable length)
 *
 *  \param handle   Handle representing the connection; returned previously by
 *                   BL_open().
 *  \param index    zero-based index of the answer data set
 *  \param type     type of data set is returned within
 *  \param length   length of data set is returned within
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getAnswerTypeByIndex(BL_HANDLE handle, const unsigned int index, BL_ANSWER_TYPE *type,
                                         size_t *length);

// ! If the last answer to a command contained additional data, then this
// function copies
// ! the answer data set over into the destination buffer. Data set selected by
// name.
/**
 *  \param handle   Handle representing the connection; returned previously by
 *                   BL_open().
 *  \param name     char*-string with the name of answer data set
 *  \param buffer   pointer to destination buffer for the data set
 *  \param length   length of destination buffer
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getAnswerByName(BL_HANDLE handle, const char *name, void *buffer, size_t length);

// ! If the last answer to a command contained additional data, then this
// function copies
// ! the answer data set over into the destination buffer. Data set selected by
// index.
/**
 *  \param handle   Handle representing the connection; returned previously by
 *                   BL_open().
 *  \param index    zero-based index of the answer data set
 *  \param buffer   pointer to destination buffer for the data set
 *  \param length   length of destination buffer
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getAnswerByIndex(BL_HANDLE handle, const unsigned int index, void *buffer, size_t length);

/** @}*/

/** \addtogroup l_pull_handling
 *  \brief List of legacy functions to pull retrieved data from a connection
 *
 *  The following functions are used to get data which has been recieved from a
 * BabyLIN-device.
 *  This apporach uses the pull method, i.e. you will not get any information
 * pushed ( see \ref l_callback_handling "Callback Handling" ) when it's
 * received.
 *  Instead you have to call these functions whenever you want to get retrieved
 * data.
 *  These functions are outdated and no longer used for the new BabyLIN API.
 *  @{
 */

// ! Fetches the next frame on Channel from the receiver queue.
// ! Note: The Device fills the receiver queue only if command "disframe" sent
// before.
/**
 *  \param handle     Handle representing the connection; returned previously by
 *                    getChannelHandle().
 *  \param framedata  Pointer to a  frame_t structure.
 *  \return           Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000)
 * getLastChannelError().
 */
int BL_DLLIMPORT BL_getNextFrame(BL_HANDLE handle, BL_frame_t *framedata);
int BL_DLLIMPORT BL_getNextFrameTimeout(BL_HANDLE handle, BL_frame_t *framedata, int timeout_ms);

// ! Fetches the frame with frame ID from the receiver queue.
// ! Note: The Baby-LIN fills the receiver queue only if command "disframe" sent
// before.
/**
 *  \param handle     Handle representing the connection; returned previously by
 *                    connectDevice().
 *  \param frameNr    Number of Frame do you received in queue.
 *  \param framedata  Pointer to a  BL_frame_t structure.
 *  \return           Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000)
 * getLastChannelError().
 */
int BL_DLLIMPORT BL_getLastFrame(BL_HANDLE handle, int frameNr, BL_frame_t *framedata);

// ! Fetches the next signal from the receiver queue.
// ! Note: The Baby-LIN fills the receiver queue only if command "dissignal"
// sent before.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                      BL_open().
 *  \param signaldata  Pointer to a  BL_signal_t structure.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getNextSignal(BL_HANDLE handle, BL_signal_t *signaldata);

// ! Fetches the next LIN-bus error from the receiver queue.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                      BL_open().
 *  \param errordata   Pointer to a  BL_error_t structure.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getNextBusError(BL_HANDLE handle, BL_error_t *errordata);

// ! Fetches the next complete DTL request from the receiver queue.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param frame       Pointer to a  BL_dtl_t structure.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getNextDTLRequest(BL_HANDLE handle, BL_dtl_t *frame);

// ! Fetches the next complete DTL response from the receiver queue.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param frame       Pointer to a  BL_dtl_t structure.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getNextDTLResponse(BL_HANDLE handle, BL_dtl_t *frame);

// ! Returns the current signal value (for non-array signals).
// ! Note: The Baby-LIN reports the signal value only if command "dissignal"
// sent before.
/** Special signalNr '-1' returns always 4711 in *value; signalNr '-2' returns a
 * counter
 *  increased by 1 after every call.
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param signalNr    Number of the signal accordng to SDF.
 *  \param value       Pointer to an word-sized variable getting the value.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getSignalValue(BL_HANDLE handle, int signalNr, unsigned short *value);

// ! Returns the current signal value (for non-array signals).
// ! Note: The Baby-LIN reports the signal value only if command "dissignal"
// sent before.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param signalName  Name of the Signal as declared in LDF.
 *  \param value       Pointer to an word-sized variable getting the value.
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getSignalValueByName(BL_HANDLE handle, const char *signalName, unsigned short *value);

// ! Returns the current signal value (for array signals).
// ! Note: The Baby-LIN reports the signal value only if command "dissignal"
// sent before.
/** Special signalNr '-1' returns always the hex array { 0x01, 0x23, 0x45, 0x67,
 * 0x89, 0xab, 0xcd, 0xef } in *array;
 *  signalNr '-2' returns a counted sequence, where the byte 0 holds the actual
 * counter and the following bytes hold
 *  the 'history'; i.e.:
 *
 *    1st call: { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 *    2nd call: { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 *    3rd call: { 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 *    4th call: { 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 *                ...etc...
 *
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param signalNr    Number of the signal accordng to SDF.
 *  \param array       Pointer to an 8 byte array getting the value. It must
 * always have the size
 *                     of 8 bytes, even for smaller array signals!
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getSignalArray(BL_HANDLE handle, int signalNr, unsigned char *array);

// ! Returns the current signal value (for array signals).
// ! Note: The Baby-LIN reports the signal value only if command "dissignal"
// sent before.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param signalName  Name of the Signal as declared in LDF.
 *  \param array       Pointer to an 8 byte array getting the value. It must
 * always have the size
 *                     of 8 bytes, even for smaller array signals!
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_getSignalArrayByName(BL_HANDLE handle, const char *signalName, unsigned char *array);

// ! Returns the SignalType about of given signal entry.
/**
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param idx         Zero based index of requested signal entry.
 *  \return            Status of operation; Signal is Array == 1; Signal is
 * Skala Value == 0.
 */
int BL_DLLIMPORT BL_isSignalArray(BL_HANDLE handle, int idx);

// ! Encodes the signal's value as defined in the corresponding Signal Encoding
// tables of LDF/SDF.
/** If no SignalEncoding is specified for this signal, the value itself is
 * written into destination buffer 'description'.
 *  If one of the required pointers is NULL or the buffer size is too small, the
 * function returns the needed minimum buffer
 *  length in 'length'.
 *  It's possible to use two variants to get encoded signal:
 *    1) pointer 'encUnit' and 'buffLen1' set to NULL: then encoded signal saved
 * inclusive unit in buffer 'encSignal'
 *    2) pointer 'encUnit' and 'buffLen1' != NULL: unit of signal saved
 * separately in buffer 'encUnit'
 *  \param handle      Handle representing the connection; returned previously
 * by
 *                     BL_open().
 *  \param signalNr    Number (Index) of the signal accordng to SDF.
 *  \param value       Value to be encoded
 *  \param encSignal   points to save location of encoded signal value
 * (inclusive 'unit', if 'encUnit' not used)
 *  \param buffLen0    length of 'encSignal' buffer
 *  \param encUnit     optional: points to save location of signal unit (if this
 * pointer is NULL then 'unit' saved in 'encSignal' buffer also)
 *  \param buffLen1    optional: length of 'encUnit' buffer (if this pointer is
 * NULL then 'unit' saved in 'encSignal' buffer also)
 *  \return            Status of operation; '=0' means successful, '!=0'
 * otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000)
 * BL_getLastError().
 */
int BL_DLLIMPORT BL_encodeSignal(BL_HANDLE handle, int signalNr, unsigned int value, char *encSignal, size_t *buffLen0,
                                 char *encUnit, size_t *buffLen1);
int BL_DLLIMPORT BL_getSignalsInFrame(BL_HANDLE handle, int frameNr, BL_signal_t *signalList, int signalListLen);
int BL_DLLIMPORT BL_getSignalDataFromFrame(BL_HANDLE handle, BL_frame_t *frame, int signalIdx, BL_signal_t *signal);

/**
 * @brief Returns some details for given frame entry.
 *
 * @param handle      Handle representing the connection; returned previously
 * by BL_open()
 * @param idx         Zero based index of requested frame entry (sdf number).
 * @param plinid      Pointer to int, which gets filled with LIN ID
 * (without parity bits).
 * @param psize	      Pointer to int, which gets filled with size of frame
 * in bytes.
 * @param pnodenum	   Pointer to int, which gets filled with nodeindex of
 * publishing node for this frame.
 * @param pframetype  Pointer to int, which gets filled with Lin version of
 * this frame.
 *
 * @return BL_OK on success, errocoe otherwise
 */
int BL_DLLIMPORT BL_getFrameDetails(BL_HANDLE handle, int idx, int *plinid, int *psize, int *pnodenum, int *pframetype);

/** @}*/

#if defined(__cplusplus)
}  // extern "C"
#endif

#endif  // BabyLIN_old.h
