#ifndef BABYLINRETURNCODES_H
#define BABYLINRETURNCODES_H

#if !defined(BL_DLLIMPORT)
#   if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#       if BUILD_DLL
#           define BL_DLLIMPORT __declspec(dllexport) __stdcall
#       else /* Not BUILDING_DLL */
// #           define BL_DLLIMPORT __declspec (dllimport)
#           define BL_DLLIMPORT  __stdcall
#       endif /* Not BUILDING_DLL */
#   else
#       define BL_DLLIMPORT
#   endif
#else
// #undef BL_DLLIMPORT
// #define BL_DLLIMPORT
#endif

/** \addtogroup return_values Return Values
 *  \brief List of possible return values of BabyLINDLL functions
 *
 *  The following values may be returned by BL_ and BLC_ functions to indicate the success or failure of an operation.
 *  Mostly, the functions will return BL_OK as an indicator for success. However, some functions use positive values to return the result of the function on success
 * ( for example BL_getFrameCount will return the number of frames )
 *  @{
 */
// ! Function successfully completed.
#define BL_OK                                 0
// ! Limit for separating BabyLIN- and PC-side errors; below there are all PC-side ones.
#define BL_PC_SIDE_ERRORS               -100000
// ! Internal resource allocation problem. Maybe out of memory/handles/etc.
#define BL_RESOURCE_ERROR               -100001
// ! Specified handle invalid.
#define BL_HANDLE_INVALID               -100002
// ! There is no connection open.
#define BL_NO_CONNECTION                -100003
// ! Serial port couldn't be opened or closed.
#define BL_SERIAL_PORT_ERROR            -100004
// ! BabyLIN command syntax error.
#define BL_CMD_SYNTAX_ERROR             -100005
// ! BabyLIN doesn't answer within timeout.
#define BL_NO_ANSWER                    -100006
// ! Unable to open a file.
#define BL_FILE_ERROR                   -100007
// ! Wrong parameter given to function.
#define BL_WRONG_PARAMETER              -100008
// ! No data available upon request.
#define BL_NO_DATA                      -100009
// ! No SDF was loaded previously
#define BL_NO_SDF                       -100010
// ! Internal message format error
#define BL_DP_MSG_ERROR                 -100011
// ! The given signal_nr or name does not exist in loaded SDF
#define BL_SIGNAL_NOT_EXISTENT          -100012
// ! The signal chosen is a scalar, but an array function was called
#define BL_SIGNAL_IS_SCALAR             -100013
// ! The signal chosen is an array, but an scalar function was called
#define BL_SIGNAL_IS_ARRAY              -100014
// ! The SDF is unsupported by connected Baby-LIN
#define BL_SDF_INSUFFICIENT_FIRMWARE    -100015
// ! The given signal has no encoding
#define BL_ENCODING_NOT_EXISTENT        -100016
// ! The given buffer is too small
#define BL_BUFFER_TOO_SMALL             -100017
// ! There is no additional answer data present from last sendCommand-call
#define BL_NO_ANSWER_DATA               -100018
// ! Additional data with given index/name not present
#define BL_ANSWER_DATA_NOT_EXISTENT     -100019
// ! Device Supported no Channels
#define BL_NO_CHANNELS_AVAILABLE        -100020
// ! Unknown command passed to sendCommand
#define BL_UNKNOWN_COMMAND              -100021
// ! a sendCommand message timed out
#define BL_TIMEOUT                      -100022
// ! sdf can not be loaded to a the device due to incompatibibility ( incompatible SDFV3 to SDFV2 device )
#define BL_SDF_INCOMPATIBLE             -100023
// ! sdf can not be loaded to a the device due to incompatibibility ( incompatible SDFV3 to SDFV2 device )
#define BL_DOWNLOAD_IN_PROGRESS         -100026

#define SDF_OK              0
// ! value passed as a SDF handle is not valid
#define SDF_HANDLE_INVALID -100024
// ! sdf can not be unloaded as the SDF is in use on a device
#define SDF_IN_USE         -100025

/** @}*/

/**
 * \brief type of an answer data token
 *  retrieve type using BLC_getAnswerTypeByName or BLC_getAnswerTypeByIndex
 */
typedef enum {
    // ! token is an integer value
    BL_ANSWER_TYPE_INT,
    // ! token is a string value
    BL_ANSWER_TYPE_STR,
    // ! token is an binary value
    BL_ANSWER_TYPE_BIN,
} BL_ANSWER_TYPE;

/**
 * \brief DTL protocol status answers
 * part of BLC_DTL data structure
 * retrieve status of pending DTL actions using BLC_getDTLRequestStatus or BLC_getDTLResponseStatus
 */
typedef enum {
    // ! DTL action completed
    LD_COMPLETED = 0,
    // ! DTL action failed
    LD_FAILED,
    // ! DTL action in progress
    LD_IN_PROGRESS,
} BL_DTL_STATUS;

#endif // BABYLINRETURNCODES_H
