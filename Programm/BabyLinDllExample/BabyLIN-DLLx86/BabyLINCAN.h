#ifndef BABYLIN_H
#define BABYLIN_H

#include "BabyLINReturncodes.h"

/** \addtogroup structures Data Structures
 *  \brief List of BabyLIN structures
 *
 *  The following structures are used to retrieve data from a running BabyLIN device like frame- and signal-reports or error and debug information
 *  @{
 */

/** \brief Information about a BabyLIN port on the host operating system
 *
 * The structure holds information about a BabyLIN device connected to the PC
 * Use @ref BLC_getBabyLinPorts to retrieve a list of connected BabyLIN-Devices
 *
 * */
typedef struct
{
    /** \brief the COM-port number the device is connected to (windows only), use this value for BLC_open
    */
    int portNr;
    /** \brief the type of interface of the connected device (0=USBSerial, 1=Network UDP, 2=Network TCP)
    */
    int type;
    /** \brief the name of the connected device (f.ex. BabyLIN RM-II)
    */
    char name[256];
    /** \brief the linux device file the BabyLIN is connected to (linux only)
    */
    char device[256];
}BLC_PORTINFO;

/** \brief Information about a connected BabyLIN device
 *
 * The structure holds information about a connected BabyLIN device
 * retreive informations using BLC_getTargetID or request by using \ref BLC_sendCommand with command "targetid"
 *
 */
typedef struct
{
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

    // ! Firmware version of the device
    unsigned short version;

    // ! Firmware build number
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

    // ! number of channels
    long numofchannels;

    // ! Textual name of the device (zero-terminated C-string)
    char name[128];
} BLC_TARGETID;

// ! \brief represents a connection to a BabyLIN-device or one of the channels
typedef void *BL_HANDLE;
typedef const char *CPCHAR;

/**
 * \brief Information about a channel on a BabyLIN device
 *
 * Return data of the command 'BLC_getChannelInfo' providing information about a channel (BUS-type, speed etc.)
 */
typedef struct
{
    // ! Channel-id(i.e. 0 = device channel)
    unsigned short id;

    // ! Channel-Type(i.e. 0 = LIN, 1 = CAN, 99 = DEVICE)
    unsigned short type;

    // ! Textual name of the Channel (zero-terminated C-string)
    char name[128];

    // ! Maximum Baudrate of Channel
    long maxbaudrate;

    ///! Reserved value (ignore for now)
    long reserved1;

    // ! Reserved value (ignore for now)
    long reserved2;

    // ! Reserved value (ignore for now)
    long reserved3;

    // ! the number of the section of the loaded sdf associated with this channel
    // ! >= 0 means valid section number, -1: no mapping or no sdf loaded
    int associatedWithSectionNr;
} BLC_CHANNELINFO;

// ! Return data of the command @ref BLC_getSDFInfo
typedef struct
{
    // ! Filename of the loaded sdf
    char filename[256];

    // ! number of sections in the SDF. A file consists of at least one Section (LIN, CAN or DEVICE)
    short sectionCount;

    // ! SDF-version
    short version_major, version_minor;
}BLC_SDFINFO;

// ! Return data of the command \ref BLC_getSectionInfo
typedef struct
{
    // ! Textual name of the Section (zero-terminated C-string) as defined using SessionConf
    char name[128];

    // ! Channel-Type(i.e. 0 = LIN, 1 = CAN, 99 = DEVICE)
    int type;

    // ! Number of the section within the SDF ( zero-based index )
    short nr;
}BLC_SECTIONINFO;

// ! Carries information about one frame, is used as API interface
typedef struct _BLC_FRAME
{
    // ! Id of the channel within the device
    unsigned long chId;

    // ! Global time index of frame transmission start (in us). Received from target, represents the time since the Target was powered on.
    unsigned long timestamp;

    // ! Timestamp with pc time, used to calculate age of framedata, to allow timeout functions
    long intime;

    // ! FrameID of Frame ( as appeared on the BUS. On LIN BUS without parity bits )
    unsigned long frameId;

    // ! Length of frameData
    unsigned char lenOfData;

    // ! Databytes of the frame
    unsigned char frameData[8];

    /** @brief Additional, informational frame flags
     *
     * Used as a bitfield, multiple flags possible
     * | Value | Description |
     * |------:|:------------|
     * |0x01   |Frame has error|
     * |0x02   |Frame is selfsent (sent by the BabyLIN-Device, because it simulates the corresponding node)|
     * |0x04   |Timebase, if set, the unit of @ref timestamp is ms, otherwise us|
     **/
    short frameFlags;

    /** \brief Bus specific flags
     *
     * for LIN-BUS:
     * Used as a bitfield, multiple flags possible
     * | Value | Description |
     * |------:|:------------|
     * | 0x01  |Valid CLASSIC checksum (V1)|
     * | 0x02  |Valid EXTENDED checksum (V2)|
     * | 0x04  |incomplete frame without checksum, not an error|
     * | 0x08  |Errorframe (f.ex: no data)|
     * | 0x10  |Frame is slaveresponse to a master request. If set, the upper 3 bits of flags denote a master request id|
     * | 0x20  |Event triggered frame ( only if 0x10 is not set )|
     * */
    short busFlags;

    /** @brief checksum of the frame
     * stores a checksum V1 or V2 ( refer to busFlags which checksum type applies )
     */
    unsigned char checksum;
} BLC_FRAME;

// ! Carries information about one frame, is used as API interface
typedef struct
{
    // ! Id of the channel within the device
    unsigned long chId;

    // ! Global time index of frame transmission start (in us). Received from target, represents the time since the Target was powered on.
    unsigned long timestamp;

    // ! Timestamp with pc time, used to calculate age of framedata, to allow timeout functions
    long intime;

    // ! FrameID of Frame ( as appeared on the BUS. On LIN BUS without parity bits )
    unsigned long frameId;

    // ! Length of frameData
    unsigned int lenOfData;

    // ! Databytes of the frame
    unsigned char frameData[1024];

    /** @brief Additional, informational frame flags
     *
     * Used as a bitfield, multiple flags possible
     * | Value | Description |
     * |------:|:------------|
     * |0x01   |Frame has error|
     * |0x02   |Frame is selfsent (sent by the BabyLIN-Device, because it simulates the corresponding node)|
     * |0x04   |Timebase, if set, the unit of @ref timestamp is ms, otherwise us|
     **/
    short frameFlags;

    /** \brief Bus specific flags
     *
     * for LIN-BUS:
     * Used as a bitfield, multiple flags possible
     * | Value | Description |
     * |------:|:------------|
     * | 0x01  |Valid CLASSIC checksum (V1)|
     * | 0x02  |Valid EXTENDED checksum (V2)|
     * | 0x04  |incomplete frame without checksum, not an error|
     * | 0x08  |Errorframe (f.ex: no data)|
     * | 0x10  |Frame is slaveresponse to a master request. If set, the upper 3 bits of flags denote a master request id|
     * | 0x20  |Event triggered frame ( only if 0x10 is not set )|
     * */
    short busFlags;

    /** @brief checksum of the frame
     * stores a checksum V1 or V2 ( refer to busFlags which checksum type applies )
     */
    unsigned char checksum;
} BLC_JUMBO_FRAME;

/**
 * \brief status of a macro
 *
 * Information about a macro, used as parameter of a callback function registered by @ref BLC_registerMacroStateCallback
 *
 * */
typedef struct
{
    // ! channel number this information belongs to
    int channelid;

    /** \brief macro-number the information is about
     * */
    int macronr;

    /** \brief the macro command number currently executed
     *
     * denotes the command-number in the macro @ref macronr which is currently executed
     *
     * valid if @ref state denotes a running macro
     * */
    int cmdnr;

    /**
     * @brief state of the macro execution
     *
     * |Value|Description|
     * |----:|:----------|
     * |0x00 |Macro execution ended|
     * |0x01 |Macro execution started|
     * |0x02 |Macro execution running|
     * |0x03 |Macro execution error|
     */
    int state;

    /**
     * @brief timestamp of the macro state
     *
     */
    long timestamp;
}BLC_MACROSTATE;

// ! Carries information about one signal.
typedef struct
{
    // ! Index number of signal; see the SDF for the adequate number
    int index;
    // ! Defines wether this signal is a normal, value-based one (0) or LIN2.0 array signal (1).
    int isArray;
    // ! Value of the signal.
    unsigned long long value;
    // ! Length of the array.
    int arrayLength;
    // ! Value(s) of the signal, if isArray == 1.
    unsigned char array[8];
    // ! Global time index of frame transmission start (in �sec).
    unsigned long timestamp;
    // ! Current Channelid
    unsigned short chId;
} BLC_SIGNAL;

// ! Represents a LIN error message
typedef struct
{
    /** \brief Time of occurence.
     * The timestamp when the error occurred.
     *
     * device-timstamp in us if error @ref type is a device error (1-13)
     *
     * pc timestamp in ms if error @ref type is dll error (65535)
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
     * |11|ERRTYPE_BUSSPEED_DIFFERS|Actual bus-speed differs from LDF bus speed (Warning) |actual speed|
     * |12|ERRTYPE_KWP_ERROR|Error in KWP|KWP error code|
     * |13|ERRTYPE_APPLICATION|Application error|unused|
     * |14|ERRTYPE_RESP_LOST|Response send buffer overflow occured|unused|
     * |15|ERRTYPE_CAN_NOERR|CAN error disappeared|unused|
     * |16|ERRTYPE_CAN|CAN error| bitmap 0x01 noAck \n bitmap 0x02 stuffing error \n bitmap 0x04 framing error \n bitmap 0x08 recessive bit error \n bitmap 0x10 dominant bit error \n bitmap 0x20 checksum error|
     * |65535|ERRTYPE_DLL_ERROR|Error in DLL occurred|dll status code|
     * */
    unsigned short type;
    /** \brief Additional error information
     *
     * Depends on @ref type descriptions.
     * for "dll status code":
     * |status|description|
     * |-----:|:----------|
     * |1|Lost connection to device|
     * */
    unsigned short status;
} BLC_ERROR;

// ! Carries information about DTL protocol (both requests and responses).
typedef struct  _BLC_DTL
{
    // ! Status of protocol frame
    BL_DTL_STATUS status;

    // ! NAD of protocol frame
    unsigned char nad;

    // ! Length of the data-array.
    int length;
    // ! frame data, beginning with the (R)SID.
    unsigned char data[4*1024];
} BLC_DTL;

typedef struct _BLC_EVENT
{
    unsigned int timestamp;
    unsigned int pc_timestamp;
    int event;
    long long data;
} BLC_EVENT;

/** @}*/

/** \addtogroup callback_handling Callback Handling
 *  \brief List of functions to manage callback functions
 *
 *  The following functions are used to register callback functions for a BabyLIN connection.
 *  A callback will be called whenever a corresponding message is recieved on the connection it is registered to ( push method ).
 *  If you want to use a pull method to retrieve the data, have a look at the \ref pull_handling "Pull Methods" section of the documentation
 *  @{
 */

// !these Callbacks will tell you the data(as done with old callbacks) AND the Channel which send the Data
// !to find out which Device send the data use =>
// !BL_HANDLE hConnection = BLC_getConnectionOfChannel(BLC_CHANNEL hChannel);
typedef void (BLC_frame_callback_func)(BL_HANDLE, BLC_FRAME frame);
typedef void (BLC_jumboframe_callback_func)(BL_HANDLE, BLC_JUMBO_FRAME frame);
typedef void (BLC_signal_callback_func)(BL_HANDLE, BLC_SIGNAL signal); // will also be called on Frame event, if registered
typedef void (BLC_macrostate_callback_func)(BL_HANDLE, BLC_MACROSTATE macroState);
typedef void (BLC_error_callback_func)(BL_HANDLE, BLC_ERROR error);
typedef void (BLC_debug_callback_func)(BL_HANDLE, const char *text);
typedef void (BLC_dtl_request_callback_func)(BL_HANDLE, BLC_DTL frame);
typedef void (BLC_dtl_response_callback_func)(BL_HANDLE, BLC_DTL frame);

// !these Callbacks will tell you the data(as done with old callbacks), plus the Channel which send the Data and a user data pointer
// !added when registering the function
// !to find out which Device send the data use =>
// !BL_HANDLE hConnection = BLC_getConnectionOfChannel(BLC_CHANNEL hChannel);
typedef void (BLC_frame_callback_func_ptr)(BL_HANDLE, BLC_FRAME frame, void *);
typedef void (BLC_jumboframe_callback_func_ptr)(BL_HANDLE, BLC_JUMBO_FRAME frame, void *);
typedef void (BLC_signal_callback_func_ptr)(BL_HANDLE, BLC_SIGNAL signal, void *); // will also be called on Frame event, if registered
typedef void (BLC_macrostate_callback_func_ptr)(BL_HANDLE, BLC_MACROSTATE macroState, void *);
typedef void (BLC_error_callback_func_ptr)(BL_HANDLE, BLC_ERROR error, void *);
typedef void (BLC_debug_callback_func_ptr)(BL_HANDLE, const char *text, void *);
typedef void (BLC_dtl_request_callback_func_ptr)(BL_HANDLE, BLC_DTL frame, void *);
typedef void (BLC_dtl_response_callback_func_ptr)(BL_HANDLE, BLC_DTL frame, void *);
typedef void (BLC_event_callback_func_ptr)(BL_HANDLE, BLC_EVENT event, void *);

#if defined(__cplusplus)
    #include <cstddef>                  // get "size_t"�, used by function BL_encodeSignal())
    #include <cstdint>
extern "C" {
#else
    #include <stddef.h>                 // get "size_t"�, used by function BL_encodeSignal())
    #include <stdint.h>
#endif

/** \brief Registers a callback function, which is called on every reception of a (monitored) jumbo frame.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel id which the frame occurred
 * \param callback    Pointer to a function call-compatible to  @ref BLC_jumboframe_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerJumboFrameCallback(BL_HANDLE handle, BLC_jumboframe_callback_func *callback);

/** \brief Registers a callback function, which is called on every reception of a (monitored) frame.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel id which the frame occurred
 * \param callback    Pointer to a function call-compatible to  @ref BLC_frame_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerFrameCallback(BL_HANDLE handle, BLC_frame_callback_func *callback);

/** \brief Registers a callback function, which is called on every reception of a (monitored) signal.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel on which the signal occurred;
 * \param callback    Pointer to a function call-compatible to @ref BLC_signal_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerSignalCallback(BL_HANDLE handle, BLC_signal_callback_func *callback);

/** \brief Registers a callback function, which is called on every reception of an error message
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_error_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerErrorCallback(BL_HANDLE handle, BLC_error_callback_func *callback);
/** \brief Registers a callback function, which is called whenever the execution state of a macro changes
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_macrostate_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerMacroStateCallback(BL_HANDLE handle, BLC_macrostate_callback_func *callback);
/** \brief Registers a callback function, which is called whenever a debug message from a BabyLIN-Device is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_debug_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerDebugCallback(BL_HANDLE handle, BLC_debug_callback_func *callback);
/** \brief Registers a callback function, which is called whenever dtl request is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_dtl_request_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerDTLRequestCallback(BL_HANDLE handle, BLC_dtl_request_callback_func *callback);
/** \brief Registers a callback function, which is called whenever dtl response is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_dtl_request_callback_func.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerDTLResponseCallback(BL_HANDLE handle, BLC_dtl_request_callback_func *callback);

/** \brief Registers a callback function, which is called on every reception of a (monitored) jumbo frame.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel id which the frame occurred
 * \param callback    Pointer to a function call-compatible to  @ref BLC_jumboframe_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_jumboframe_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataJumboFrameCallback(BL_HANDLE handle, BLC_jumboframe_callback_func_ptr *callback, void *userdata);

/** \brief Registers a callback function, which is called on every reception of a (monitored) frame.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel id which the frame occurred
 * \param callback    Pointer to a function call-compatible to  @ref BLC_frame_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_frame_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataFrameCallback(BL_HANDLE handle, BLC_frame_callback_func_ptr *callback, void *userdata);

/** \brief Registers a callback function, which is called on every reception of a event report.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel id which the event occurred
 * \param callback    Pointer to a function call-compatible to  @ref BLC_event_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_event_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataEvent(BL_HANDLE handle, BLC_event_callback_func_ptr *callback, void *userdata);

/** \brief Registers a callback function, which is called on every reception of a (monitored) signal.
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel on which the signal occurred;
 * \param callback    Pointer to a function call-compatible to @ref BLC_signal_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_signal_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataSignalCallback(BL_HANDLE handle, BLC_signal_callback_func_ptr *callback, void *userdata);

/** \brief Registers a callback function, which is called on every reception of an error message
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_error_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataErrorCallback(BL_HANDLE handle, BLC_error_callback_func_ptr *callback, void *userdata);
/** \brief Registers a callback function, which is called whenever the execution state of a macro changes
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_macrostate_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataMacroStateCallback(BL_HANDLE handle, BLC_macrostate_callback_func_ptr *callback, void *userdata);
/** \brief Registers a callback function, which is called whenever a debug message from a BabyLIN-Device is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_debug_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataDebugCallback(BL_HANDLE handle, BLC_debug_callback_func_ptr *callback, void *userdata);
/** \brief Registers a callback function, which is called whenever dtl request is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_dtl_request_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataDTLRequestCallback(BL_HANDLE handle, BLC_dtl_request_callback_func_ptr *callback, void *userdata);
/** \brief Registers a callback function, which is called whenever dtl response is received
 *
 * Issuing a NULL-pointer de-registers the callback function. As the function is called
 * from another thread context, take care of thread-safety (i.e. using mutexes, etc.).
 * \param handle      Handle representing the channel emitting the error; returned previously by
 * \param callback    Pointer to a function call-compatible to @ref BLC_dtl_request_callback_func_ptr.
 * \param userdata    Pointer to custom user data to pass to @ref BLC_error_callback_func_ptr.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) BLC_getLastError.
 */
int BL_DLLIMPORT BLC_registerUserDataDTLResponseCallback(BL_HANDLE handle, BLC_dtl_request_callback_func_ptr *callback, void *userdata);
/** @}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @}*/

/** \addtogroup connection_handling Connection Handling
 *  \brief List of BabyLIN connection handling and device information functions
 *
 *  The following functions are used to setup a connection to a BabyLIN device.
 *  @{
 */

/** \brief Get the major and minor version number of the library
 *
 *  \deprecated use @ref BLC_getExtendedVersion instead
 *
 *  This function retreives the version in the given parameter variables of the
 *  library.
 *  \param major    major part of version number.
 *  \param minor    minor part of version number.
 */
void BL_DLLIMPORT  BLC_getVersion(int *major, int *minor);

/** \brief Get the major, minor and patch version number of the library
 *
 *  This function retreives the version in the given parameter variables of the
 *  library.
 *  \param major    major part of version number.
 *  \param minor    minor part of version number.
 *  \param patch    patch part of version number.
 *  \param buildrev build revision of version number.
 */
void BL_DLLIMPORT  BLC_getExtendedVersion(int *major, int *minor, int *patch, int *buildrev);

/** \brief Get the version string of the library
 *
 *  This function returns the version string of the library.
 *  \return         returns a C-string with the version information.
 */
CPCHAR BL_DLLIMPORT   BLC_getVersionString(void);

/** \brief Retrieve a list of ports a BabyLIN is connected to
 *
 * The function doesn't try to connect to the found Ports
 * wraps @ref BLC_getBabyLinPortsTimout with timout value set to 1000ms
 *
 * \param portListToBeFilled array to be filled
 * \param pFoundPortCount the length of the array to be filled
 * \return the number of connected BabyLINs found (>=0) or < 0 on error
 *
 *
 * example: \code{.c}
 *          BLC_PORTINFO ports[2];
            int maxPortCount = 2;
 *          int foundCount = BLC_getBabyLinPorts(ports, &maxPortCount);
            int foundEmpty = BLC_getBabyLinPorts(NULL, NULL);
            // if there where 3 BabyLin connected to usb:
            // foundCount == 2
            // foundEmpty == 3

            //if there is only 1 Babylin connected:
            foundCount = BLC_getBabyLinPorts(ports, &maxPortCount);
            foundEmpty = BLC_getBabyLinPorts(NULL, NULL);
            //foundEmpty == 1;
            //foundCount == 1;
            \endcode
 *
 */
int BL_DLLIMPORT BLC_getBabyLinPorts(BLC_PORTINFO portListToBeFilled[], int *pFoundPortCount);

/** \brief Retrieve a list of ports a BabyLIN is connected to
 *
 * The function doesn't try to connect to the found Ports
 * \param portListToBeFilled array to be filled
 * \param pFoundPortCount the length of the array to be filled
 * \param timoutms a timeout value in ms to wait for replies of network devices
 * \return the number of connected BabyLINs found (>=0) or < 0 on error
 */
int BL_DLLIMPORT BLC_getBabyLinPortsTimout(BLC_PORTINFO portListToBeFilled[], int *pFoundPortCount, int timoutms);

/** \brief Open a connection to a BabyLIN USB-Serial device.
 *
 *  This function tries to open the designated port and to start communication
 *  with the device.
 *  \param port     the port, the BabyLIN is connected to. It uses Windows-style numbering,
 *                  which means it starts with '1' for the first serial port.
 *                  '0' is reserved.
 *                  On linux systems, the port is represented by the path to the device file ("/dev/ttyUSB0" f.ex.)
 *  \return         Returns an handle for the BabyLIN-connection or NULL if the connection could not be established.
 *                  You may fetch the corresponding (textual) error with @ref BLC_getLastError.
 */
#if defined(_WIN32)
BL_HANDLE BL_DLLIMPORT  BLC_open(unsigned int port);
#else
BL_HANDLE BL_DLLIMPORT  BLC_open(const char *port);
#endif

/** \brief Open a connection to a BabyLIN device using ethernet.
 *
 *  This function tries to open the designated ip and port and to start communication
 *  with the device.
 *  \param ip       the ip-address of the BabyLIN to connect to
 *  \param port     the ip-port of the BabyLIN toconnected to
 *  \return         Returns an handle for the BabyLIN-connection or NULL if the connection could not be established.
 *                  You may fetch the corresponding (textual) error with @ref BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT  BLC_openNet(const char *ip, int port);

/** \brief Open a connection to a BabyLIN USB device.
 *
 *  This function tries to open the designated port and to start communication
 *  with the device.
 *  \param device   the usb device string, the BabyLIN is connected to.
 *  \return         Returns an handle for the BabyLIN-connection or NULL if the connection could not be established.
 *                  You may fetch the corresponding (textual) error with @ref BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT  BLC_openUSB(const char *device);

/** \brief Open a connection to a BabyLIN device using BLC_PORTINFO information.
 *
 *  This function tries to open the BabyLIN device of the BLC_PORTINFO information, i.e. works as a wrapper for
 * @ref BLC_open and @ref BLC_openNet which automatically decides which connection to establish.
 *
 * \note Platform independent way of connecting to BabyLIN-devices found by @ref BLC_getBabyLinPorts or @ref BLC_getBabyLinPortsTimout
 *
 *  \param portInfo       the BLC_PORTINFO-structure of the BabyLIN to connect to ( see @ref BLC_getBabyLinPorts )
 *  \return         Returns an handle for the BabyLIN-connection or NULL if the connection could not be established.
 *                  You may fetch the corresponding (textual) error with @ref BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT  BLC_openPort(BLC_PORTINFO portInfo);

/** \brief convert a device url to BLC_PORTINFO to use in BLC_openPort
 *
 * this function tries to convert a given url to a complete struct of type BLC_PORTINFO.
 *
 * \param url   the device url to convert
 * \return      BL_OK on success, error code otherwise (in case of error, the BLC_PORTINFO structure is left untouched)
 */
int BL_DLLIMPORT  BLC_convertUrl(const char *url, BLC_PORTINFO *portInfo);

/** \brief Close connection to Device.
 *
 * close an open connection, given by handle.
 * \param handle   Handle representing the connection ( see @ref BLC_open )
 * \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                 See standard return values for error, or for textual
 *                 representation  BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_close(BL_HANDLE handle);

/** \brief Close ALL connections to ALL Devices.
 *
 *  close all open connections all handles are invalidated
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_closeAll(void);

/** \brief Reset the BabyLIN device to an consistent and deactivated state.
 *
 * Afterwards, the device will no longer monitor the bus, neither acting as slave
 * nor as master.
 * \param handle   Handle representing a channel; returned previously by
 *                 BLC_getChannelHandle().
 * \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                 See standard return values for error, or for textual
 *                 representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_flush(BL_HANDLE handle);

/** \brief Requests the information about the target
 *
 *  \param handle    Handle representing the connection (see @ref BLC_open )
 *  \param targetID  pointer to pre-allocated @ref BLC_TARGETID structure to hold the information
 *                   after the successful call
 *  \return          Status of operation; '=0' means successful, '!=0' otherwise.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getTargetID(BL_HANDLE handle, BLC_TARGETID *targetID);

/** \brief Returns the unique hardware type identifier for a device
 *
 *  \param handle    Handle representing the connection ( see @ref BLC_open )
 *  \return          The hardware type or BabyLIN-error return code. See (@ref BLC_TARGETID.type) for hardware types.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getHWType(BL_HANDLE handle);

/** \brief number of channels provided by the BabyLIN-Device
 *
 *  \param handle   Handle representing the connection (see @ref BLC_open)
 *  \return         number of channels >= 0 or < 0 on error.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getChannelCount(BL_HANDLE handle);

/** \brief Retrieve a handle to the specified channel
 *
 *  This function returns a channel-handle for the specified channelId.
 *  A channel-handle is used to control a LIN- or CAN-BUS on the BabyLIN-device.
 *
 *  \param handle    Handle representing the Device connection ( see @ref BLC_open )
 *  \param channelId Identifier for the channel to get the handle of.
 *                   Ranges from 0 to the number of channels supported by the device (see @ref BLC_getChannelCount)
 *  \return          handle to the channel, 0 on error
 *                   You may fetch the corresponding (textual) with @ref BLC_getLastError.
 */
BL_HANDLE BL_DLLIMPORT  BLC_getChannelHandle(BL_HANDLE handle, int channelId);

/** \brief Retrieve informations about the Channel
 *
 * \param handle    Channelhandle representing the Channel. (see @ref BLC_getChannelHandle)
 * \param pinfo     pointer to pre-allocated @ref BLC_CHANNELINFO structure to hold the information
 *                  after the successful call
 * \return          Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getChannelInfo(BL_HANDLE handle, BLC_CHANNELINFO *pinfo);

/** \brief Returns a C-string with the textual representation of the last error.
 *
 *  Get a textual error message for Errorcodes < -1000.
 *
 *  \param handle   Handle to the erroneous connection or channel.
 *  \param pErrorBuffer pointer to allocated memory buffer to store error message
 *  \param bufferLength allocated length of pErrorBuffer
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getLastError(BL_HANDLE handle, char *pErrorBuffer, int bufferLength);

/** \brief Resets the BabyLIN device to an consistent and deactivated state.
 *
 * Afterwards, the device will no longer monitor the bus, neither acting as slave
 * nor as master.
 * \param handle   Handle representing the connection. (see @ref BLC_open )
 * \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                 See standard return values for error, or for textual
 *                 representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_Reset(BL_HANDLE handle);

/** @}*/

/** \addtogroup sdf_handling SDF Information
 *  \brief List of functions to get information about the loaded SDF
 *
 *  The following functions are used to retrieve information about the elements in a loaded SDF-file.
 *  @{
 */

/** \brief Loads the specified SDF-file into library and optionally the BabyLIN device.
 *
 * The SDF is generated by LINWorks/SessionConf from a LDF file.
 * \warning this resets the device upon download
 *
 * \param handle     Handle representing the connection. (see @ref BLC_open )
 * \param filename   C-string with the (fully qualified) filename (i.e. "mybus.sdf", if
 *                   in the same directory, or "c:/data/mybus.sdf").
 * \param download   boolean value, determines if the SDF profile gets downloaded into
 *                   the BabyLIN device (!=0) or only used in the library (=0).
 * \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_loadSDF(BL_HANDLE handle, const char *filename, int download);

/** \brief Loads the specified LDFile into library and optionally the BabyLIN device.
 *
 * Loads a given LDF, converts the LDF to a SDF ( without SDF specific features ) and optionally downloads the generated SDF to the device
 * \warning this resets the device upon download
 *
 * \param handle     Handle representing the connection. (see @ref BLC_open )
 * \param filename   C-string with the (fully qualified) filename (i.e. "mybus.ldf", if
 *                   in the same directory, or "c:/data/mybus.ldf").
 * \param download   boolean value, determines if the generated SDF profile gets downloaded into
 *                   the BabyLIN device (!=0) or only used in the library (=0).
 * \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_loadLDF(BL_HANDLE handle, const char *filename, int download);

/** \brief Loads the previously loaded SDF-file into the BabyLIN device.
 *
 * The SDF could be generated by LINWorks/SessionConf from a LDF file and must have been
 * loaded previously by an BL_loadSDF() command.
 * WARNING: this resets the device!
 * \param handle     Handle representing the connection. (see @ref BLC_open )
 * \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_downloadSDF(BL_HANDLE handle, int mode);

/** \brief Retrieve further Information about a loaded SDF
 *
 * Need a loaded SDF (see @ref BLC_loadSDF or @ref BLC_loadLDF )
 * \param handle    handle to a valid connection
 * \param pSDFInfo  points to a pre-allocated @ref BLC_SDFINFO to be filled with information
 * \return          Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 * */
int BL_DLLIMPORT  BLC_getSDFInfo(BL_HANDLE handle, BLC_SDFINFO *pSDFInfo);

/** \brief Retrieve informations about a SDF-Section from a loaded SDF
 *
 *
 * \param handle handle of a valid connection
 * \param infoAboutSectionNr    the section number to retrieve information of.
 *                              Ranges from 0 to the number of sections in the loaded SDF (see @ref BLC_getSDFInfo and @ref BLC_SDFINFO.sectionCount )
 * \param pSectionInfo          address of a pre-allocated @ref BLC_SECTIONINFO
 * \return                      Status of operation; '=0' means successful, '!=0' otherwise.
 *                              See standard return values for error, or for textual
 *                              representation (for return values < -1000) @ref BLC_getLastError.
 * */
int BL_DLLIMPORT  BLC_getSectionInfo(BL_HANDLE handle, int infoAboutSectionNr, BLC_SECTIONINFO *pSectionInfo);

/** \brief Retrieve description string of a SDF-Section from a loaded SDF
 *
 *
 * \param handle handle of the channel to get the sdf section description of
 * \return
 * */
CPCHAR BL_DLLIMPORT  BLC_getChannelSectionDescription(BL_HANDLE handle);

/** \brief Returns the number of nodes on the BUS
 *
 * Number of nodes connected to the bus according to the informations in the loaded SDF.
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \return            Number of nodes connected to the bus according to the informations in the loaded SDF.
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNodeCount(BL_HANDLE handle);

/** \brief Returns the name of a given node
 *
 * Name of a node connected to the bus according to the informations in the loaded SDF.
 *  \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 *  \param idx         Zero based index of requested node entry (see @ref BLC_getNodeCount )
 *  \param dstbuf      Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 *  \param buflen      How many bytes should get returned.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNodeName(BL_HANDLE handle, int idx, char *dstbuf, int buflen);

/** \brief Returns the number of frames of the BUS description
 *
 * Number of frames of the bus according to the informations in the loaded SDF.
 *  \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 *  \return            Number of frames of the bus according to the informations in the loaded SDF.
 *                     Values <0 on error.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getFrameCount(BL_HANDLE handle);

/** \brief Returns the name of a given frame
 *
 * Name of a frame of the bus according to the informations in the loaded SDF.
 *  \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 *  \param idx         Zero based index of requested frame entry (see @ref BLC_getFrameCount )
 *  \param dstbuf      Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 *  \param buflen      How many bytes should get returned.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getFrameName(BL_HANDLE handle, int idx, char *dstbuf, int buflen);

/** \brief Returns the number of signals
 *
 * Number of signals of the bus according to the informations in the loaded SDF.
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \return            Number of signals of the bus according to the informations in the loaded SDF.
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getSignalCount(BL_HANDLE handle);

/** \brief Returns the name of given signal
 *
 * Name of a signal of the bus according to the informations in the loaded SDF.
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \param idx         Zero based index of requested signal entry (see @ref BLC_getSignalCount )
 * \param dstbuf      Pointer to char array which gets filled (must hold min. 'buflen' bytes).
 * \param buflen      How many bytes should get returned.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getSignalName(BL_HANDLE handle, int idx, char *dstbuf, int buflen);

/** \brief Retrieve information about wheather a signal is emulated by the BabyLIN-Device or not
 *
 * A signal is emulated if the node to which it belongs (according to the SDF) is emulated by the BabyLIN-Device
 * (see "setnodesimu" sendCommand in \ref babylin_commands_sdf to change node emulation at runtime )
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \param idx         Zero based index of requested signal entry (see @ref BLC_getSignalCount )
 * \return            '=0' means signal is not emulated, '=1' if emulated, '<0' denotes error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_isSignalEmulated(BL_HANDLE handle, int idx);

/** \brief Retrieve size of a signal
 *
 * Size of a signal of the bus according to the informations in the loaded SDF.
 *  \param handle     Handle representing a channel (see @ref BLC_getChannelHandle )
 *  \param idx        Zero based index of requested signal entry (see @ref BLC_getSignalCount )
 *  \return           size of the signal in bits.
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getSignalSize(BL_HANDLE handle, int idx);

/** \brief Retrieve the number of signals mapped in a frame
 *
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \param idx         Zero based index of requested frame entry (see @ref BLC_getFrameCount )
 * \return            Number of signals mapped in the frame
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getSignalsInFrameCount(BL_HANDLE handle, int idx);

/** \brief Retrieve the signal number of a signal mapped in a frame
 *
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \param frameIndex  Zero based index of the frame the signal is mapped to (see @ref BLC_getFrameCount )
 * \param signalIndex Zero based index of the signal as mapped to the frame (see @ref BLC_getSignalsInFrameCount )
 * \return            Zero based index of the signal in the SDF
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getSignalInFrame(BL_HANDLE handle, int frameIndex, int signalIndex);

/** \brief Retrieve the SDF frame number for a given BUS frame-id
 *
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \param frameId     the BUS frameId to get the frame number
 * \return            Zero based index of the frame in the SDF
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getFrameNrForFrameId(BL_HANDLE handle, uint32_t frameId);

/** \brief Retrieve the BUS frame-id for a given SDF frame
 *
 * \param handle      Handle representing a channel (see @ref BLC_getChannelHandle )
 * \param frameNr     Zero based index of the frame (see @ref BLC_getFrameCount )
 * \return            BUS frameId to the given frame index
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getFrameIdForFrameNr(BL_HANDLE handle, unsigned char frameNr);

/** @}*/

/** \addtogroup commands Command Functions
 *  \brief List of functions to send commands to a BabyLIN device
 *
 *  The following functions are used to send commands to a BabyLIN device to set or retrieve simulation or device parameters.
 *  @{
 */

/** \brief Send a (raw!) command to the BabyLIN device.
 *
 * \warning The command must be encoded in the binary DP-Message format of BabyLIN.
 *
 * \param handle   Handle representing the connection. (see @ref BLC_open )
 * \param command  char*-Buffer with the designated command(s).
 * \param length   length of buffer; gets set to actual sent command's length.
 * \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                 See standard return values for error, or for textual
 *                 representation (for return values < -1000)  BL_getLastError().
 */
int BL_DLLIMPORT  BLC_sendRaw(BL_HANDLE handle, const unsigned char *command, unsigned int *length);

/** \brief Set the Diagnostic Transport Layer mode.
 *
 *  There are different Diagnostic modes, which offer different levels of protocol functionality.
 *  The Baby-LIN will start with Diagnostic OFF on Power Up.
 *  If the BabyLIN acts as LIN master then the selection of an Diagnostic Mode happens trough the usage
 *  of the appropriate API function calls. So the API functions BL_sendRawMasterRequest or BL_sendRawSlaveResponse
 *  will start  the Diagnostic RAW mode, where as the API calls BL_sendDTLRequest or BL_sendDTLResponse will start the
 *  Diagnostic DTL mode.
 *  If the BabyLIN acts as LIN slave then the DTL mode must be set by use of this function.
 *  It is not possible to use different Diagnostics modes at the same time !
 *
 * List of DTL modes:
 * | Mode | Name | Description |
 * |-----:|:-----|:------------|
 * |0 | DTL_NONE | no DTL Support |
 * |1 | DTL_RAW  | RAW Mode DTL Support |
 * |2 | DTL_COOKED | Cooked Mode DTL Support |
 *
 *  \param handle      Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \param mode        DTL mode
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_setDTLMode(BL_HANDLE handle, int mode);

/** \brief Send a DTL MasterReq to a node
 *
 *  \param handle      Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \param nad         NAD of the node the request gets send to.
 *  \param length      Length of the following data array.
 *  \param data        DTL frame data (begins with SID, followed by up to 4095 data bytes).
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT   BLC_sendDTLRequest(BL_HANDLE handle, unsigned char nad, int length, unsigned char *data);

/** \brief Send a DTL SlaveResp to a node
 *
 *  \param handle      Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \param nad         NAD of the node the response gets send for.
 *  \param length      Length of the following data array.
 *  \param data        DTL frame data (begins with RSID, followed by up to 4095 data bytes).
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) BL_getLastError().
 */
int BL_DLLIMPORT   BLC_sendDTLResponse(BL_HANDLE handle, unsigned char nad, int length, unsigned char *data);

/** \brief Send a (non-DTL) SlaveResp upon receive of matching MasterReq
 *
 *  Upon the reveive of the next MasterReq frame, every bit of the request is compared to
 *  'reqdata' if the corresponding bit of 'reqmask' is set (1). If all match, Baby-LIN starts
 *  to send out the data given in 'data', 8 bytes with each SlaveResp frame.
 *
 *  \param handle     Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \param reqdata    Data of the expected MasterReq (exactly 8 bytes).
 *  \param reqmask    Mask for 'reqdata' to indicate which bits must match (exactly 8 bytes).
 *  \param data       MasterReq frame data (multiple of 8 bytes).
 *  \param length     Length of data to send.
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT   BLC_sendRawSlaveResponse(BL_HANDLE handle, unsigned char *reqdata, unsigned char *reqmask, unsigned char *data, int length);

/** \brief Send a (non-DTL) MasterReq with the specified 8 bytes as data.
 *
 *  The internal raw-SlaveResponse-buffer is being reset and the Baby-LIN device gets
 *  instructed to report the next 'count' SlaveResp-frames which in turn are accumulated
 *  into the SlaveResponse-buffer which can be queried by BL_getRawSlaveResponse().
 *
 *  \param handle      Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \param data        MasterReq frame data (exactly 8 bytes).
 *  \param count       Number of expected SlaveResp frames.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT   BLC_sendRawMasterRequest(BL_HANDLE handle, unsigned char *data, int count);

/** \brief Returns the status of the last request-send operation.
 *
 *  \param handle      Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \return            Status of last request operation if >= 0; see @ref BL_DTL_STATUS for
 *                     values. For < 0, see standard return values for error, or for
 *                     textual representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getDTLRequestStatus(BL_HANDLE handle);

/** \brief Returns the status of the last resonse-send operation.
 *
 *  \param handle      Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \return            Status of last request operation if >= 0; see @ref BL_DTL_STATUS for
 *                     values. For < 0, see standard return values for error, or for
 *                     textual representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getDTLResponseStatus(BL_HANDLE handle);

/** \brief Returns the first 'count' bytes of the current SlaveResp-buffer.
 *
 *  The internal raw-SlaveResponse-buffer is filled continuously with the data bytes of
 *  reported SlaveResp-frames and is being reset upon every call of BL_sendRawMasterRequest().
 *
 *  \param handle      Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \param data        Pointer to char array which gets filled (must hold min. 'length' bytes).
 *  \param length      How many bytes should get returned.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT   BLC_getRawSlaveResponse(BL_HANDLE handle, unsigned char *data, int length);

int BL_DLLIMPORT    BLC_updRawSlaveResponse(BL_HANDLE handle);

/** \brief Returns BL_OK if the last answer to a command contained additional data.
 *
 *  If there is no additional data present it returns BL_NO_ANSWER_DATA.
 *  \param handle   Handle representing a LIN-channel (see @ref BLC_getChannelHandle )
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_lastAnswerHasData(BL_HANDLE handle);

/** \brief get type of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function reports
 * the type and size for a specific answer data set. Data set selected by name.
 * The following types of data sets are possible:
 *      BL_ANSWER_TYPE_INT - 32bit integer
 *      BL_ANSWER_TYPE_STR - zero-terminated string (variable length)
 *      BL_ANSWER_TYPE_BIN - binary data (variable length)
 *
 *  \param handle   Handle representing the channel on which the answer data was received (see @ref BLC_getChannelHandle )
 *  \param name     char*-string with the name of answer data set
 *  \param type     type of data set is returned within
 *  \param length   length of data set is returned within
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getAnswerTypeByName(BL_HANDLE handle, const char *name, BL_ANSWER_TYPE *type, size_t *length);

/** \brief get type of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function reports
 * the type and size for a specific answer data set. Data set selected by index.
 * The following types of data sets are possible:
 *      BL_ANSWER_TYPE_INT - 32bit integer
 *      BL_ANSWER_TYPE_STR - zero-terminated string (variable length)
 *      BL_ANSWER_TYPE_BIN - binary data (variable length)
 *
 *  \param handle   Handle representing the channel on which the answer data was received (see @ref BLC_getChannelHandle )
 *  \param index    zero-based index of the answer data set
 *  \param type     type of data set is returned within
 *  \param length   length of data set is returned within
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getAnswerTypeByIndex(BL_HANDLE handle, const unsigned int index, BL_ANSWER_TYPE *type, size_t *length);

/** \brief get name of a parameter of the last answer data from a BabyLIN
 *
 *  \param handle   Handle representing the channel on which the answer data was received (see @ref BLC_getChannelHandle )
 *  \param name     char*-string with the name of answer data set
 *  \param type     type of data set is returned within
 *  \param length   length of data set is returned within
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getAnswerNameByIndex(BL_HANDLE handle, int index, char *nameBuffer, int *nameBufferLength);

/** \brief get the value of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function copies
 * the answer data set over into the destination buffer. Data set selected by name.
 *
 *  \param handle   Handle representing the channel on which the answer data was received (see @ref BLC_getChannelHandle )
 *  \param name     char*-string with the name of answer data set
 *  \param buffer   pointer to destination buffer for the data set
 *  \param length   length of destination buffer
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getAnswerByName(BL_HANDLE handle, const char *name, void *buffer, size_t length);

/** \brief get the value of a parameter of the last answer data from a BabyLIN
 *
 * If the last answer to a command contained additional data, then this function copies
 * the answer data set over into the destination buffer. Data set selected by index.
 *
 *  \param handle   Handle representing the channel on which the answer data was received (see @ref BLC_getChannelHandle )
 *  \param index    zero-based index of the answer data set
 *  \param buffer   pointer to destination buffer for the data set
 *  \param length   length of destination buffer
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getAnswerByIndex(BL_HANDLE handle, const unsigned int index, void *buffer, size_t length);

/** \brief Send a command to the BabyLIN device.
 *
 * The command must match the command syntax as specified in the BabyLIN
 * documentation (see @ref babylin_commands). The trailing ';' may be omitted; you may specify
 * several commands at once! LIKE "start; disframe 0 1; stop"

 *  \param handle   Handle representing the channel to send the command to (see @ref BLC_getChannelHandle )

 *  \param command  C-string with the command (i.e. "status;")

 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_sendCommand(BL_HANDLE handle, const char *command);

/** \brief shorthand for "setsig" command (see @ref babylin_commands)
 *
 *  \param handle   Handle representing the channel to send the command to (see @ref BLC_getChannelHandle )
 *  \param signalNr the signal to set the value
 *  \param value    the value to assign to the signal
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_setsig(BL_HANDLE handle, int signalNr, unsigned long long value);

/** \brief shorthand for "mon_set" command (see @ref babylin_commands)
 *
 *  \param handle   Handle representing the channel to send the command to (see @ref BLC_getChannelHandle )
 *  \param frameid  the BUS-frame-id to set the framedata for
 *  \param databytes  array of databytes to use as the framedata
 *  \param len      the length of the data
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_mon_set(BL_HANDLE handle, int frameid, const int *databytes, int len);

/** \brief shorthand for "mon_xmit" command (see @ref babylin_commands)
 *
 *  \param handle   Handle representing the channel to send the command to (see @ref BLC_getChannelHandle )
 *  \param frameid  the BUS-frame-id to transmit
 *  \param slottime slottime = 0 equals a single transmit, slottime > 0 equals cyclic transmission of frame
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_mon_xmit(BL_HANDLE handle, int frameId, int slottime);

/** \brief shorthand for "mon_set" followed by "mon_xmit" command (see @ref babylin_commands)
 *
 *  \param handle   Handle representing the channel to send the command to (see @ref BLC_getChannelHandle )
 *  \param frameid  the BUS-frame-id to set and transmit
 *  \param databytes  array of databytes to use as the framedata
 *  \param len      the length of the data
 *  \param slottime slottime = 0 equals a single transmit, slottime > 0 equals cyclic transmission of frame
 *  \return         Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -10000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_mon_set_xmit(BL_HANDLE handle, int frameId, const int *databytes, int len, int slottime);
/** @}*/

/** \addtogroup pull_handling Pull Methods
 *  \brief List of functions to pull retrieved data from a connection
 *
 *  The following functions are used to get data which has been recieved from a BabyLIN-device.
 *  This apporach uses the pull method, i.e. you will not get any information pushed ( see \ref callback_handling "Callback Handling" ) when it's received.
 *  Instead you have to call these functions whenever you want to get retrieved data.
 *  @{
 */

/** \brief Retrieve the last framedata available for a frame
 *
 * \important The Baby-LIN fills the receiver queue only if command "disframe" sent before ( see @ref babylin_commands )
 *
 *  \param handle     Handle representing the channel to get the frame data from (see @ref BLC_getChannelHandle )
 *  \param frameNr    Zero based index of requested frame entry.
 *  \param framedata  Pointer to a pre-allocated BLC_FRAME structure.
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getLastFrame(BL_HANDLE handle, int frameNr, BLC_FRAME *framedata);

/** \brief Fetches the next frame on Channel from the receiver queue.
 *
 * \important The Device fills the receiver queue only if command "disframe" sent before.
 *
 *  \param handle     Handle representing the channel to get the frame data from (see @ref BLC_getChannelHandle )
 *  \param framedata  Pointer to a pre-allocated BLC_FRAME structure.
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextFrame(BL_HANDLE handle, BLC_FRAME *framedata);

/** \brief Fetches the next frames on channel from the receiver queue.
 *
 * \important The device fills the receiver queue only if command "disframe" sent before.
 *
 *  \param handle     Handle representing the channel to get the frame data from (see @ref BLC_getChannelHandle )
 *  \param framedata  Pointer to a pre-allocated BLC_FRAME (structure) array.
 *  \param size       Input/Output parameter. On input, size of the pre-allocated BLC_FRAME (structure) array,
 *                    in units of BLC_FRAME, which must be a positive value.
 *                    On output, the actual number of retrieved BLC_FRAMEs, which might be less
 *                    than *size on input.
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextFrames(BL_HANDLE handle, BLC_FRAME *framedata, int *size);

/** \brief Fetches the next frame on Channel from the receiver queue with wait-timeout
 *
 * Retrieves the next frame received from the BabyLIN.
 * If no frame-data is available, the funktion will wait _up to_ timeout_ms milliseconds
 * for new data before it returns with a BL_TIMEOUT returncode
 * \important The Device fills the receiver queue only if command "disframe" sent before.
 *
 *  \param handle     Handle representing the channel to get the frame data from (see @ref BLC_getChannelHandle )
 *  \param framedata  Pointer to a pre-allocated BLC_FRAME structure.
 *  \param timeout_ms timout to wait for new framedata
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextFrameTimeout(BL_HANDLE handle, BLC_FRAME *framedata, int timeout_ms);

/** \brief Fetches the next frames on channel from the receiver queue with wait-timeout
 *
 * Retrieves the next frames received from the BabyLIN.
 * If no frame-data is available, the funktion will wait _up to_ timeout_ms milliseconds
 * for new data before it returns with a BL_TIMEOUT returncode
 * \important The Device fills the receiver queue only if command "disframe" sent before.
 *
 *  \param handle     Handle representing the channel to get the frame data from (see @ref BLC_getChannelHandle )
 *  \param framedata  Pointer to a pre-allocated BLC_FRAME structure.
 *  \param timeout_ms timout to wait for new framedata
 *  \param size       Input/Output parameter. On input, size of the pre-allocated BLC_FRAME (structure) array,
 *                    in units of BLC_FRAME, which must be a positive value.
 *                    On output, the actual number of retrieved BLC_FRAMEs, which might be less
 *                    than *size on input.
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextFramesTimeout(BL_HANDLE handle, BLC_FRAME *framedata, int timeout_ms, int *size);

/** \brief Fetches the next signal from the receiver queue.
 *
 * \important The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 *  \param handle      Handle representing the channel to get the signal data from (see @ref BLC_getChannelHandle )
 *  \param signaldata  Pointer to a pre-allocated BLC_SIGNAL structure.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextSignal(BL_HANDLE handle, BLC_SIGNAL *signaldata);

/** \brief Fetches the next signals from the receiver queue.
 *
 * \important The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 *  \param handle      Handle representing the channel to get the signal data from (see @ref BLC_getChannelHandle )
 *  \param signaldata  Pointer to a pre-allocated BLC_SIGNAL (structure) array.
 *  \param size        Input/Output parameter. On input, size of the pre-allocated BLC_SIGNAL (structure) array,
 *                     in units of BLC_SIGNAL, which must be a positive value.
 *                     On output, the actual number of retrieved BLC_SIGNALs, which might be less
 *                     than *size on input.
 *  \return            Status of operation; '=0' means successful, '!=' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextSignals(BL_HANDLE handle, BLC_SIGNAL *signaldata, int *size);

/** \brief Fetches the next signals for a specific signal from the receiver queue.
 *
 * \important The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 * \important this function will remove the signal values from the queue. Further signal receiving is no longer guaranteed to be in order.
 *
 *  \param handle      Handle representing the channel to get the signal data from (see @ref BLC_getChannelHandle )
 *  \param signaldata  Pointer to a pre-allocated BLC_SIGNAL (structure) array.
 *  \param size        Size of the pre-allocated BLC_SIGNAL (structure) array,
 *                     in units of BLC_SIGNAL, which must be a positive value.
 * \param signalNumber the signal number to get the signals for
 *  \return            number of signals found, '<0' on error.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextSignalsForNumber(BL_HANDLE handle, BLC_SIGNAL *signaldata, int size, int signalNumber);

/** \brief Fetches the next Bus error from the receiver queue.
 *
 *  \param handle      Handle representing the channel to get the error data from (see @ref BLC_getChannelHandle )
 *  \param errordata   Pointer to a pre-allocated BLC_ERROR structure.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextBusError(BL_HANDLE handle, BLC_ERROR *errordata);

/** \brief Fetches the next complete DTL request from the receiver queue.
 *
 *  \param handle      Handle representing the channel to get the dtl data from (see @ref BLC_getChannelHandle )
 *  \param frame       Pointer to a pre-allocated BLC_DTL structure.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextDTLRequest(BL_HANDLE handle, BLC_DTL *frame);

/** \brief Fetches the next complete DTL response from the receiver queue.
 *
 *  \param handle      Handle representing the channel to get the dtl data from (see @ref BLC_getChannelHandle )
 *  \param frame       Pointer to a pre-allocated BLC_DTL structure.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_getNextDTLResponse(BL_HANDLE handle, BLC_DTL *frame);

/** \brief  Return the current signal value (for non-array signals).
 * \important The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 * \note Special signalNr '-1' returns always 4711 in *value; signalNr '-2' returns a counter
 * increased by 1 after every call.
 *
 * \param handle      Handle representing the channel to get the signal value from (see @ref BLC_getChannelHandle )
 * \param signalNr    Number of the signal according to SDF.
 * \param value       Pointer to an word-sized variable getting the value.
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalValue(BL_HANDLE handle, int signalNr, unsigned long long *value);

/** \brief  Return the current signal value (for non-array signals) with timestamp
 * \important The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 * \note Special signalNr '-1' returns always 4711 in *value; signalNr '-2' returns a counter
 * increased by 1 after every call.
 *
 * \param handle      Handle representing the channel to get the signal value from (see @ref BLC_getChannelHandle )
 * \param signalNr    Number of the signal according to SDF.
 * \param value       Pointer to an word-sized variable getting the value.
 * \param timestamp   Pointer to an word-sized variable getting the timestamp when the signal was received (PC-Timestamp).
 * \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalValueWithTimestamp(BL_HANDLE handle, int signalNr, unsigned long long *value, unsigned long long *timestamp);

/** \brief Returns the current signal value (for non-array signals).
 *
 * \important The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 *  \param handle      Handle representing the channel to get the signal value from (see @ref BLC_getChannelHandle )
 *  \param signalName  Name of the Signal as declared in LDF.
 *  \param value       Pointer to an word-sized variable getting the value.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalValueByName(BL_HANDLE handle, const char *signalName, unsigned long long *value);

/** \brief Returns the current signal value (for array signals).
 *
 * \important The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 * \note
 * Special signalNr '-1' returns always the hex array { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef } in *array;
 *  signalNr '-2' returns a counted sequence, where the byte 0 holds the actual counter and the following bytes hold
 *  the 'history'; i.e.:
 *
 * \par
 * 1st call: { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 * 2nd call: { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 * 3rd call: { 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 * 4th call: { 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 *                ...etc...
 *
 *  \param handle      Handle representing the channel to get the signal value from (see @ref BLC_getChannelHandle )
 *  \param signalNr    Number of the signal accordng to SDF.
 *  \param array       Pointer to an 8 byte array getting the value. It must always have the size
 *                     of 8 bytes, even for smaller array signals!
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalArray(BL_HANDLE handle, int signalNr, unsigned char *array);

/** \brief Returns the current signal value (for array signals) with timstamp.
 *
 * \important The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 * \note
 * Special signalNr '-1' returns always the hex array { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef } in *array;
 *  signalNr '-2' returns a counted sequence, where the byte 0 holds the actual counter and the following bytes hold
 *  the 'history'; i.e.:
 *
 * \par
 * 1st call: { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 * 2nd call: { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 * 3rd call: { 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 * 4th call: { 0x03, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 }
 *
 * \par
 *                ...etc...
 *
 *  \param handle      Handle representing the channel to get the signal value from (see @ref BLC_getChannelHandle )
 *  \param signalNr    Number of the signal accordng to SDF.
 *  \param array       Pointer to an 8 byte array getting the value. It must always have the size
 *                     of 8 bytes, even for smaller array signals!
 *  \param timestamp   Pointer to an word-sized variable getting the timestamp when the signal was received (PC-Timestamp).
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalArrayWithTimestamp(BL_HANDLE handle, int signalNr, unsigned char *array, unsigned long long *timestamp);

/** \brief Returns the current signal value (for array signals).
 *
 * \important The Baby-LIN reports the signal value only if command "dissignal" sent before.
 *
 *  \param handle      Handle representing the channel to get the signal value from (see @ref BLC_getChannelHandle )
 *  \param signalName  Name of the Signal as declared in LDF.
 *  \param array       Pointer to an 8 byte array getting the value. It must always have the size
 *                     of 8 bytes, even for smaller array signals!
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT BLC_getSignalArrayByName(BL_HANDLE handle, const char *signalName, unsigned char *array);

/** \brief Returns the type of a signal
 *
 *  \param handle      Handle representing the channel to which the signal belongs (see @ref BLC_getChannelHandle )
 *  \param idx         Zero based index of requested signal entry.
 *  \return            Status of operation; Signal is Array == 1; Signal is scalar Value == 0.
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_isSignalArray(BL_HANDLE handle, int idx);

/** \brief Encodes the signal's value as defined in the corresponding Signal Encoding tables of LDF/SDF.
 *
 *  If no SignalEncoding is specified for this signal, the value itself is written into destination buffer 'description'.
 *  If one of the required pointers is NULL or the buffer size is too small, the function returns the needed minimum buffer
 *  length in 'length'.
 *  It's possible to use two variants to get encoded signal:
 *    1) pointer 'encUnit' and 'buffLen1' set to NULL: then encoded signal saved inclusive unit in buffer 'encSignal'
 *    2) pointer 'encUnit' and 'buffLen1' != NULL: unit of signal saved separately in buffer 'encUnit'
 *  \param handle      Handle representing the channel to which the signal belongs (see @ref BLC_getChannelHandle )
 *  \param signalNr    Number (Index) of the signal accordng to SDF.
 *  \param value       Value to be encoded
 *  \param encSignal   points to save location of encoded signal value (inclusive 'unit', if 'encUnit' not used)
 *  \param buffLen0    length of 'encSignal' buffer
 *  \param encUnit     optional: points to save location of signal unit (if this pointer is NULL then 'unit' saved in 'encSignal' buffer also)
 *  \param buffLen1    optional: length of 'encUnit' buffer (if this pointer is NULL then 'unit' saved in 'encSignal' buffer also)
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLC_encodeSignal(BL_HANDLE handle, int signalNr, unsigned long long value, char *encSignal, size_t *buffLen0, char *encUnit, size_t *buffLen1);

/** \brief Get values of all signals mapped to a frame
 *
 * \param handle    Handle representing the channel to which the frame belongs (see @ref BLC_getChannelHandle )
 * \param frameNr   frame number (according to SDF) to get the signal data from
 * \param signalList pre-allocated array of BLC_SIGNAL structures to store the signal data to
 * \param signalListLen length of the pre-allocated array of BLC_SIGNAL structures
 * \return          the number of signals stored to signalList.
 *                    Values <0 on error.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 * */
int BL_DLLIMPORT  BLC_getSignalsInFrame(BL_HANDLE handle, int frameNr, BLC_SIGNAL *signalList, int signalListLen);

/**
  * @brief Returns some details for given frame entry.
  *
  *
  * @param idx         Zero based index of requested frame entry (sdf number).
  * @param pbusid	   Pointer to int, which gets filled with BUS ID (without parity bits on LIN-Bus )
  * @param psize	   Pointer to int, which gets filled with size of frame in bytes
  * @param pnodenum	   Pointer to int, which gets filled with nodeindex of publishing node for this frame
  * @param pframetype  Pointer to int, which gets filled with LIN version of this frame (LIN channel only)
  */
int BL_DLLIMPORT   BLC_getFrameDetails(BL_HANDLE handle, int idx, int *pbusid, int *psize, int *pnodenum, int *pframetype);

/**
  * @brief Returns some details for given frame entry.
  *
  * @param handle      Handle representing the channel to which the signal belongs (see @ref BLC_getChannelHandle )
  * @param signalNr    Zero based index of the signal entry (sdf number).
  * \return            the number of the node the signal is published by.
  *                    -1 if signal is virtual.
  *                    Values <-1 on error.
  *                    See standard return values for error, or for textual
  *                    representation (for return values < -1000) @ref BLC_getLastError.
  */
int BL_DLLIMPORT   BLC_getNodeForSignal(BL_HANDLE handle, int signalNr);
/** @}*/

/** \addtogroup direct_mode Directmode
 *  \brief List of functions to access the LIN-BUS directly
 *
 *  @{
 */
int BL_DLLIMPORT   BLC_dmStart(BL_HANDLE channel, int baudrate, int /*bitwidth*/, int /*stopbits*/, int /*parity*/);
int BL_DLLIMPORT   BLC_dmWrite(BL_HANDLE channel, const char *data, unsigned int dataSize);
int BL_DLLIMPORT   BLC_dmRead(BL_HANDLE channel, char *buffer, unsigned int bufferSize);
int BL_DLLIMPORT   BLC_dmReadTimeout(BL_HANDLE channel, char *buffer, unsigned int bufferSize, unsigned int timeout_ms);
int BL_DLLIMPORT   BLC_dmPulse(BL_HANDLE channel, unsigned int lowtime_us, unsigned int paddingtime_us);
int BL_DLLIMPORT   BLC_dmStop(BL_HANDLE channel);
/** @}*/
#if defined(__cplusplus)
} // extern "C"
#endif

#endif // BABYLIN_H
