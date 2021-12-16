#ifndef BABYLINCAN_NOSTRUCT_H
#define BABYLINCAN_NOSTRUCT_H

#include "BabyLINCAN.h"

#if defined(__cplusplus)
    #include <cstddef>                  // get "size_t"�, used by function BL_encodeSignal())
    #include <cstdint>
extern "C" {
#else
    #include <stddef.h>                 // get "size_t"�, used by function BL_encodeSignal())
    #include <stdint.h>
#endif

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
BL_HANDLE BL_DLLIMPORT  BLCns_openPort(int portNr, int type, char *name, char *device);

/** \brief Requests the information about the target
 *
 *  \param handle    Handle representing the connection (see @ref BLC_open )
 *  \param targetID  pointer to pre-allocated @ref BLC_TARGETID structure to hold the information
 *                   after the successful call
 *  \return          Status of operation; '=0' means successful, '!=0' otherwise.
 *                   See standard return values for error, or for textual
 *                   representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getTargetID(BL_HANDLE handle, unsigned short *type, unsigned short *version, unsigned short *flags, long *serial, long *heapsize, long *numofchannels,
                                    char *name, int nameLength);

/** \brief Retrieve informations about the Channel
 *
 * \param handle    Channelhandle representing the Channel. (see @ref BLC_getChannelHandle)
 * \param pinfo     pointer to pre-allocated @ref BLC_CHANNELINFO structure to hold the information
 *                  after the successful call
 * \return          Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getChannelInfo(BL_HANDLE handle, unsigned short *id, unsigned short *type, char *name, int nameLength, long *maxbaudrate, long *reserved1, long *reserved2,
                                       long *reserved3, int *associatedWithSectionNr);

/** \brief Get the version string of the library
 *
 *  This function returns the version string of the library.
 *  \return         returns a C-string with the version information.
 */
int BL_DLLIMPORT   BLCns_getVersionString(char *buffer, int bufferlen);

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
int BL_DLLIMPORT  BLCns_getLastFrame(BL_HANDLE handle, int frameNr, unsigned long *chId, unsigned long *timestamp, long *intime, unsigned long *frameId, unsigned char *lenOfData,
                                     unsigned char *frameData, short *frameFlags, short *busFlags, unsigned char *checksum);

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
int BL_DLLIMPORT  BLCns_getNextFrame(BL_HANDLE handle, unsigned long *chId, unsigned long *timestamp, long *intime, unsigned long *frameId, unsigned char *lenOfData,
                                     unsigned char *frameData, short *frameFlags, short *busFlags, unsigned char *checksum);

/** \brief Fetches the next frames on Channel from the receiver queue.
 *
 * \important The Device fills the receiver queue only if command "disframe" sent before.
 *
 *  \param handle     Handle representing the channel to get the frame data from (see @ref BLC_getChannelHandle )
 *  \param chId       Array of channel identifiers for the corresponding fetched frames.
 *  \param timestamp  Array of timestamps for the corresponding fetched frames.
 *  \param intime     Array of arrival timestamps for the corresponding fetched frames.
 *  \param frameId    Array of frame identifiers for the corresponding fetched frames.
 *  \param lenOfData  Array of data lengths for the data of of the corresponding fetched frames.
 *  \param frameData  Array of frame data arrays for the corresponding fetched frames.
 *  \param frameFlags Array of frame flags for the corresponding fetched frames.
 *  \param busFlags   Array of busFlags for the corresponding fetched frames.
 *  \param checksums  Array of checksums for the corresponding fetched frames.
 *  \param size       Input/Output parameter. On input, number of BLC_FRAMEs to be fetched, which must be a positive value.
 *                    On output, the actual number of retrieved BLC_FRAMEs, which might be less
 *                    than *size on input.
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getNextFrames(BL_HANDLE handle, unsigned long chId[], unsigned long timestamp[], long intime[], unsigned long frameId[], unsigned char lenOfData[],
                                      unsigned char frameData[], short frameFlags[], short busFlags[], unsigned char checksum[], int *size);

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
int BL_DLLIMPORT  BLCns_getNextFrameTimeout(BL_HANDLE handle, unsigned long *chId, unsigned long *timestamp, long *intime, unsigned long *frameId, unsigned char *lenOfData,
                                            unsigned char *frameData, short *frameFlags, short *busFlags, unsigned char *checksum, int timeout_ms);

/** \brief Fetches the next frames on Channel from the receiver queue with wait-timeout
 *
 * Retrieves the next frame received from the BabyLIN.
 * If no frame-data is available, the funktion will wait _up to_ timeout_ms milliseconds
 * for new data before it returns with a BL_TIMEOUT returncode
 * \important The Device fills the receiver queue only if command "disframe" sent before.
 *
 *  \param handle     Handle representing the channel to get the frame data from (see @ref BLC_getChannelHandle )
 *  \param chId       Array of channel identifiers for the corresponding fetched frames.
 *  \param timestamp  Array of timestamps for the corresponding fetched frames.
 *  \param intime     Array of arrival timestamps for the corresponding fetched frames.
 *  \param frameId    Array of frame identifiers for the corresponding fetched frames.
 *  \param lenOfData  Array of data lengths for the data of of the corresponding fetched frames.
 *  \param frameData  Array of frame data arrays for the corresponding fetched frames.
 *  \param frameFlags Array of frame flags for the corresponding fetched frames.
 *  \param busFlags   Array of busFlags for the corresponding fetched frames.
 *  \param checksums  Array of checksums for the corresponding fetched frames.
 *  \param timeout_ms timout to wait for new framedata
 *  \param size       Input/Output parameter. On input, number of BLC_FRAMEs to be fetched, which must be a positive value.
 *                    On output, the actual number of retrieved BLC_FRAMEs, which might be less
 *                    than *size on input.
 *  \return           Status of operation; '=0' means successful, '!=0' otherwise.
 *                    See standard return values for error, or for textual
 *                    representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getNextFramesTimeout(BL_HANDLE handle, unsigned long chId[], unsigned long timestamp[], long intime[], unsigned long frameId[], unsigned char lenOfData[],
                                             unsigned char frameData[], short frameFlags[], short busFlags[], unsigned char checksum[], int timeout_ms, int *size);

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
int BL_DLLIMPORT  BLCns_getNextSignal(BL_HANDLE handle, int *index, int *isArray, unsigned long long *value, int *arrayLength, unsigned char *array, unsigned long *timestamp,
                                      unsigned short *chId);

/** \brief Fetches the next signals from the receiver queue.
 *
 * \important The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 *  \param handle      Handle representing the channel to get the signal data from (see @ref BLC_getChannelHandle )
 *  \param index       Output parameter: array of indices of the corresponding retrieved signals.
 *  \param isArray     Output parameter: array of boolean values, indicating if the corresponding retrieved signal is an array.
 *  \param value       Output parameter: array of signal values for the corresponding retrieved signals.
 *  \param arrayLength Output parameter: array of arrayLengths for the data arrays contained in the retrieved signals.
 *  \param array       Output parameter: array of 8*(*size) bytes, containing for each retrieved signal an 8-byte data array
 *                     if the resp. arrayLength is greater 0.
 *  \param timestamp   Output parameter: array of timestamps for the corresponding retrieved signals.
 *  \param chId        Output parameter: array of channel identifiers for the corresponding retreived signals.
 *  \param size        Input/Output parameter. On input, number of BLC_SIGNAL to be fetched, which must be a positive value.
 *                     On output, the actual number of retrieved BLC_SIGNALs, which might be less
 *                     than *size on input.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getNextSignals(BL_HANDLE handle, int index[], int isArray[], unsigned long long value[], int arrayLength[], unsigned char array[],
                                       unsigned long timestamp[], unsigned short chId[], int *size);

/** \brief Fetches the next signals for a signalnumber from the receiver queue.
 *
 * \important The Baby-LIN fills the receiver queue only if command "dissignal" sent before.
 *
 *  \param handle      Handle representing the channel to get the signal data from (see @ref BLC_getChannelHandle )
 *  \param index       Output parameter: array of indices of the corresponding retrieved signals.
 *  \param isArray     Output parameter: array of boolean values, indicating if the corresponding retrieved signal is an array.
 *  \param value       Output parameter: array of signal values for the corresponding retrieved signals.
 *  \param arrayLength Output parameter: array of arrayLengths for the data arrays contained in the retrieved signals.
 *  \param array       Output parameter: array of 8*(*size) bytes, containing for each retrieved signal an 8-byte data array
 *                     if the resp. arrayLength is greater 0.
 *  \param timestamp   Output parameter: array of timestamps for the corresponding retrieved signals.
 *  \param chId        Output parameter: array of channel identifiers for the corresponding retreived signals.
 *  \param size        Input/Output parameter. On input, number of BLC_SIGNAL to be fetched, which must be a positive value.
 *                     On output, the actual number of retrieved BLC_SIGNALs, which might be less
 *                     than *size on input.
 *  \param signalNumber the signal number to return signals for
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getNextSignalsForNumber(BL_HANDLE handle, int index[], int isArray[], unsigned long long value[], int arrayLength[], unsigned char array[],
                                                unsigned long timestamp[], unsigned short chId[], int size, int signalNumber);

/** \brief Fetches the next Bus error from the receiver queue.
 *
 *  \param handle      Handle representing the channel to get the error data from (see @ref BLC_getChannelHandle )
 *  \param errordata   Pointer to a pre-allocated BLC_ERROR structure.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getNextBusError(BL_HANDLE handle, unsigned long *timestamp, unsigned short *type, unsigned short *status);

/** \brief Fetches the next complete DTL request from the receiver queue.
 *
 *  \param handle      Handle representing the channel to get the dtl data from (see @ref BLC_getChannelHandle )
 *  \param frame       Pointer to a pre-allocated BLC_DTL structure.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getNextDTLRequest(BL_HANDLE handle, BL_DTL_STATUS *status, unsigned char *nad, int *length, unsigned char *data);

/** \brief Fetches the next complete DTL response from the receiver queue.
 *
 *  \param handle      Handle representing the channel to get the dtl data from (see @ref BLC_getChannelHandle )
 *  \param frame       Pointer to a pre-allocated BLC_DTL structure.
 *  \return            Status of operation; '=0' means successful, '!=0' otherwise.
 *                     See standard return values for error, or for textual
 *                     representation (for return values < -1000) @ref BLC_getLastError.
 */
int BL_DLLIMPORT  BLCns_getNextDTLResponse(BL_HANDLE handle, BL_DTL_STATUS *status, unsigned char *nad, int *length, unsigned char *data);

/** \brief Retrieve further Information about a loaded SDF
 *
 * Need a loaded SDF (see @ref BLC_loadSDF or @ref BLC_loadLDF )
 * \param handle    handle to a valid connection
 * \param pSDFInfo  points to a pre-allocated @ref BLC_SDFINFO to be filled with information
 * \return          Status of operation; '=0' means successful, '!=0' otherwise.
 *                  See standard return values for error, or for textual
 *                  representation (for return values < -1000) @ref BLC_getLastError.
 * */
int BL_DLLIMPORT  BLCns_getSDFInfo(BL_HANDLE handle, char *filename, short *sectionCount, short *version_major, short *version_minor);

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
int BL_DLLIMPORT  BLCns_getSectionInfo(BL_HANDLE handle, int infoAboutSectionNr, char *name, int *type, short *nr);

#if defined(__cplusplus)
} // extern "C"
#endif
#endif // BABYLINCAN_NOSTRUCT_H
