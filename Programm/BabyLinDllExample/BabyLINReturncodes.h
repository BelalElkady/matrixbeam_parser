#ifndef BABYLINRETURNCODES_H
#define BABYLINRETURNCODES_H

#if !defined(BL_DLLIMPORT)
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#define SYSTEMCALL_CONVENTION __stdcall
#if BUILD_DLL
#define BL_DLLIMPORT __declspec(dllexport) SYSTEMCALL_CONVENTION
#else /* Not BUILDING_DLL */
#define BL_DLLIMPORT SYSTEMCALL_CONVENTION
#endif /* Not BUILDING_DLL */
#else
#define SYSTEMCALL_CONVENTION
#if BUILD_DLL
#define BL_DLLIMPORT __attribute__((visibility("protected"))) SYSTEMCALL_CONVENTION
#else /* Not BUILDING_DLL */
#define BL_DLLIMPORT SYSTEMCALL_CONVENTION
#endif /* Not BUILDING_DLL */
#endif
#else
// #undef BL_DLLIMPORT
// #define BL_DLLIMPORT
#endif

#ifndef DEPRECATED
#ifdef _MSC_VER
#define DEPRECATED __declspec(deprecated)
#elif defined(__GNUC__) | defined(__clang__)
#define DEPRECATED __attribute__((__deprecated__))
#else
#define DEPRECATED
#endif
#endif

// ! @brief represents a connection to a BabyLIN-device or one of the channels
typedef void *BL_HANDLE;
typedef const char *CPCHAR;

/** @addtogroup return_values Return Values
 *  @brief List of possible return values of BabyLINDLL functions
 *
 *  The following values may be returned by BL_ and BLC_ functions to indicate
 * the success or failure of an operation.
 *  Mostly, the functions will return BL_OK as an indicator for success.
 * However, some functions use positive values to return the result of the
 * function on success
 * ( for example BL_getFrameCount will return the number of frames )
 *  @{
 */
/** Function successfully completed. */
#define BL_OK 0
#define SDF_OK 0
/** Limit for separating BabyLIN- and PC-side errors; below there are all
 * PC-side ones. */
#define BL_PC_SIDE_ERRORS -100000
/** Internal resource allocation problem. Maybe out of memory/handles/etc. */
#define BL_RESOURCE_ERROR -100001
/** Specified handle invalid. */
#define BL_HANDLE_INVALID -100002
/** There is no connection open. */
#define BL_NO_CONNECTION -100003
/** Serial port couldn't be opened or closed. */
#define BL_SERIAL_PORT_ERROR -100004
/** BabyLIN command syntax error. */
#define BL_CMD_SYNTAX_ERROR -100005
/** BabyLIN doesn't answer within timeout. */
#define BL_NO_ANSWER -100006
/** Unable to open a file. */
#define BL_FILE_ERROR -100007
/** Wrong parameter given to function. */
#define BL_WRONG_PARAMETER -100008
/** No data available upon request. */
#define BL_NO_DATA -100009
/** No SDF was loaded previously */
#define BL_NO_SDF -100010
/** Internal message format error */
#define BL_DP_MSG_ERROR -100011
/** The given signal_nr or name does not exist in loaded SDF */
#define BL_SIGNAL_NOT_EXISTENT -100012
/** The signal chosen is a scalar, but an array function was called */
#define BL_SIGNAL_IS_SCALAR -100013
/** The signal chosen is an array, but an scalar function was called */
#define BL_SIGNAL_IS_ARRAY -100014
/** The SDF is unsupported by connected Baby-LIN due to insufficient firmware
 * version */
#define BL_SDF_INSUFFICIENT_FIRMWARE -100015
/** The given signal has no encoding */
#define BL_ENCODING_NOT_EXISTENT -100016
/** The given buffer is too small */
#define BL_BUFFER_TOO_SMALL -100017
/** There is no additional answer data present from last sendCommand-call */
#define BL_NO_ANSWER_DATA -100018
/** Additional data with given index/name not present */
#define BL_ANSWER_DATA_NOT_EXISTENT -100019
/** Device Supported no Channels */
#define BL_NO_CHANNELS_AVAILABLE -100020
/** Unknown command passed to sendCommand */
#define BL_UNKNOWN_COMMAND -100021
/** a sendCommand message timed out */
#define BL_TIMEOUT -100022
/** SDF can not be loaded to a the device due to incompatibility (
 * incompatible SDFV3 to SDFV2 device ) */
#define BL_SDF_INCOMPATIBLE -100023
/** value passed as a SDF handle is not valid */
#define SDF_HANDLE_INVALID -100024
/** SDF can not be unloaded as the SDF is in use on a device */
#define SDF_IN_USE -100025
/** can not execute command because SDF download is in progress */
#define BL_DOWNLOAD_IN_PROGRESS -100026

/** the value could not be read. the reason should be documented in the help file. */
#define BLC_UA_GET_VALUE_REJECTED -100095
/** One of the parameters is invalid. Like a null pointer in a @ref BLC_getUnsignedNumber or a value, that is outside
 * of the permitted range, like setting 256 on a 8bit Number property. */
#define BLC_UA_INVALID_PARAMETER -100096
/** the property has no getter for that type e.g. a unsigned number can not be read from a Binary property. */
#define BLC_UA_NO_GETTER_DEFINED -100097
/** the property has no setter for that type e.g. a callback can not be stored into Binary property. */
#define BLC_UA_NO_SETTER_DEFINED -100098
/** the value given was not set. the reason should be documented in the help file.*/
#define BLC_UA_SET_VALUE_REJECTED -100099
/** A return value between @ref BLC_UA_REQUESTED_OBJECT_NOT_FOUND_FIRST and @ref BLC_UA_REQUESTED_OBJECT_NOT_FOUND_MAX
 * indicates that the path parameter given to one of the BLC_UnifiedAccess functions could not be resolved. The index of
 * the object, that could not be found is the return value - @ref BLC_UA_REQUESTED_OBJECT_NOT_FOUND_FIRST (this index is
 * 0 based).
 */
#define BLC_UA_REQUESTED_OBJECT_NOT_FOUND_FIRST -101100
/** The given Path should not have more then 100 objects */
#define BLC_UA_REQUESTED_OBJECT_NOT_FOUND_MAX -101200
/** A return value between @ref BLC_UA_NOT_RESOLVABLE_TAG_FIRST and @ref BLC_UA_NOT_RESOLVABLE_TAG_MAX indicates that
 * the path parameter given to one of the BLC_UnifiedAccess functions could not be found. The index of that key is the
 * return value - @ref BLC_UA_NOT_RESOLVABLE_TAG_FIRST (this index is 0 based).*/
#define BLC_UA_NOT_RESOLVABLE_TAG_FIRST -100100
/** The given Path should not have more then 100 tags */
#define BLC_UA_NOT_RESOLVABLE_TAG_MAX -100200
/** The @ref ua_service_iso_tp, is supposed to send a request but has no request data. */
#define BLC_UA_NO_REQUEST_DATA -100201
/** During the reception of the Response or the Request an invalid series of consecutive frames were detected. */
#define BLC_UA_SERVICE_FRAME_ORDER -100202
/** A Frame send by the DLL was not echoed by the BabyLIN within timeout_frame milliseconds. You might have to do a
 * disframe/mon_on with that FrameID. */
#define BLC_UA_SERVICE_TIMEOUT_SEND -100203
/** The Response was not received within timeout_response milliseconds. Maybe the Request is malformed? */
#define BLC_UA_SERVICE_TIMEOUT_RESPONSE -100204
/** A flow-control Frame send by the DLL was not echoed by the BabyLIN within timeout_frame milliseconds. You might have
 * to do a disframe/mon_on with that FrameID. */
#define BLC_UA_SERVICE_TIMEOUT_FLOWCONTROL_SEND -100205
/** The flow-control state reported by the target is not one of the known states. */
#define BLC_UA_SERVICE_FLOWCONTROL_INVALIDSTATE -100206
/** The flow-control state was "wait"(0x1) in more then max_flow_wait flow-control frames. */
#define BLC_UA_SERVICE_FLOWCONTROL_WAITSTATES -100207
/** The flow-control state was "overflow"(0x2). */
#define BLC_UA_SERVICE_FLOWCONTROL_OVERFLOW -100208

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-------Return Values from BabyLIN Devices-----------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

/** Missing or unknown SDF header. This Error occurs when a File is read that is
 * not a SDF File.  */
#define BL_ERR_SDF_HEADER 98
/** A corrupted DPMSG was received. This happens when a DPMessage contains an
 * invalid identifier. */
#define BL_ERR_DP_CORRUPT 101
/** An unexpected DPMSG was received. */
#define BL_ERR_DP_SEQUENCE 102
/** The SDF Section Type does not match the Channel Type it is loaded on to. */
#define BL_ERR_DP_MAPPING 103
/** The requested Action can not be carried out on the selected channel. */
#define BL_ERR_CHANNEL 104
/** The Section Type does not Match the Channel Type. */
#define BL_ERR_SECTION_TYPE 105
/** The Object you are trying to manipulate was never created. */
#define BL_ERR_NULLPOINTER 106
/** The Section Type does not Match the Channel Type. */
#define BL_ERR_SECTION_MAPPING 107
/** Dataflash/persistent memory could not be initialized. */
#define BL_ERR_DATAFLASH_INIT 108
/** Dataflash/persistent memory does not keep requested SDF index. */
#define BL_ERR_DATAFLASH_INDEX 109
/** Dataflash/persistent memory is to small to hold the SDF. */
#define BL_ERR_DATAFLASH_NOSPACE 110
/** Dataflash/persistent memory read or write error. */
#define BL_ERR_DATAFLASH 111
/** Licence for the requested feature is not installed. */
#define BL_ERR_LICENCE 112
/** Not sufficient Heap Space to perform the requested action. */
#define BL_ERR_HEAP_EXHAUSTED 113
/** Same as ERR_NULLPOINTER but Objects are restricted to Signals. */
#define BL_ERR_SIG_REFERENCE 114
/** Same as ERR_NULLPOINTER but Objects are restricted to Frames. */
#define BL_ERR_FRAME_REFERENCE 115
/** Same as ERR_NULLPOINTER but Objects are restricted to Configurations. */
#define BL_ERR_CFG_REFERENCE 116
/** Same as ERR_NULLPOINTER but Objects are restricted to MacroSelections. */
#define BL_ERR_MACROSEL_REFERENCE 117
/** Same as ERR_NULLPOINTER but Objects are restricted to Events. */
#define BL_ERR_EVENT_REFERENCE 118
/** Same as ERR_NULLPOINTER but Objects are restricted to SignalFunctions. */
#define BL_ERR_SIGFUNC_REFERENCE 119
/** The Loaded SDF is discarded because the checksum is wrong. */
#define BL_ERR_CRC 120
/** Same as ERR_SEQUENCE The requested Component is not yet initialized. */
#define BL_ERR_NOT_INITIALIZED 121
/** Same as ERR_FRAME_REFERENCE. */
#define BL_ERR_FRAMEID_LOOKUP_FAILED 122
/** Same as ERR_NULLPOINTER but Objects are restricted to Macros. */
#define BL_ERR_MACRO_REFERENCE 130
/** A parameter had an invalid value. */
#define BL_ERR_PARAMVALUE 200
/** Condition not be applied or is not full filled. */
#define BL_ERR_CONDITION 210
/** Invalid number of Parameters. */
#define BL_ERR_PARAMCOUNT 211
/** No more Services can be enqueued because the Service queue is full. */
#define BL_ERR_SERVICEQUEUE_EXHAUSTED 300
/** Error Parsing a parameter of a DPMSG. The parameter index will be added onto
 * resulting in the final Error code. */
#define BL_ERR_DP_PARSE 900
/** Upper limit of the reserved ERR_DP_PARSE indices. */
#define BL_ERR_DP_PARSE_TOP 980
/** Same as ERR_PARAMVALUE+x but only for Array Size. */
#define BL_ERR_DP_ARRAY_SIZE 989
/** The DPMSG does not start with a message name. */
#define BL_ERR_DP_NONAME 990
/** The DPMSG name is empty. */
#define BL_ERR_DP_NAME_TO_SHORT 991
/** Same as ERR_DP_CORRUPT. Happens when the message name field is longer then
 * the entire message. */
#define BL_ERR_DP_NAME_TO_LONG 992
/** Macro Command/Event Action is not known. */
#define BL_CMD_NOT_SUPPORTED 997
/** A not further specified Error. */
#define BL_ERR_UNDEF 998
/** An unknown Command was received. */
#define BL_ERR_UNKNOWN_CMD 999
/** A not further specified Error. */
#define BL_OPERATION_PENDING -1
/** The Macro result can not be read, because the macro is still running. */
#define BL_MACRO_STILL_RUNNING 150
/** The Macro can not be started, because the macro is still running. */
#define BL_MACRO_SAME_RUNNING 151
/** No more parallel Macros are allowed. */
#define BL_MACRO_OTHER_RUNNING 152
/** The Macro could not be started. */
#define BL_MACRO_START_FAIL 153
/** The initial Macro error value. */
#define BL_MACRO_NEVER_EXECUTED 154
/** Macro Result actually contains the error value. */
#define BL_MACRO_ERRCODE_IN_RESULT 155
/** Macro Result actually contains the exception value. */
#define BL_MACRO_EXCEPTIONCODE_IN_RESULT 156
/** @}*/

/**
 * @brief type of an answer data token
 *  retrieve type using BLC_getAnswerTypeByName or BLC_getAnswerTypeByIndex
 */
typedef enum {
  /** token is an integer value */
  BL_ANSWER_TYPE_INT,
  /** token is a string value */
  BL_ANSWER_TYPE_STR,
  /** token is an binary value */
  BL_ANSWER_TYPE_BIN,
  /** token is an 64BitInteger value */
  BL_ANSWER_TYPE_INT64,
  /** token is an Floatingpoint value */
  BL_ANSWER_TYPE_FLOAT,
  /** token is an unknown value */
  BL_ANSWER_TYPE_UNKNOWN,
} BL_ANSWER_TYPE;

/**
 * @brief DTL protocol status answers
 * part of BLC_DTL data structure
 * retrieve status of pending DTL actions using BLC_getDTLRequestStatus or
 * BLC_getDTLResponseStatus
 */
typedef enum {
  /** DTL action completed */
  LD_COMPLETED = 0,
  /** DTL action failed */
  LD_FAILED,
  /** DTL action in progress */
  LD_IN_PROGRESS,
} BL_DTL_STATUS;

#endif  // BABYLINRETURNCODES_H
