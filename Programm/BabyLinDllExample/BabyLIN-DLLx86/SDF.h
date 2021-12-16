#ifndef SDF_H
#define SDF_H

#ifndef BABYLIN_RETURCODES
#define BABYLIN_RETURCODES

#if !defined(BL_DLLIMPORT)
#   if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#       if BUILD_DLL
#           define BL_DLLIMPORT __declspec(dllexport) __stdcall
#       else /* Not BUILDING_DLL */
// #           define BL_DLLIMPORT __declspec (dllimport) __stdcall
#           define BL_DLLIMPORT __stdcall
#       endif /* Not BUILDING_DLL */
#   else
#       define BL_DLLIMPORT
#   endif
#endif

// ! \brief represents a connection to a BabyLIN-device ( for old BabyLINs ) or one of the channels on new BabyLIN-devices
typedef void *BL_HANDLE;

#endif
typedef struct
{
    int sectionNr;
    // ! Sectiontype (i.e. 0 = LIN, 1 = CAN, 99 = DEVICE)
    int type;
    char name[64];
    char description[4096];
}SDF_SECTIONINFO;

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup sdf_functions SDF handling
 *  \brief List of SDF functions
 *
 *  The following structures are used to load and retrieve data from a SDF
 *  The API allows to load and retrieve SDF informations without an existing BabyLIN-Device connection and is particulaly useful for SDF prelaoding
 *  or SDF loading to download to multiple BabyLIN devices.
 *
 *  @{
 */

#define SDF_OK              0
#define SDF_HANDLE_INVALID -100024
#define SDF_IN_USE         -100025

typedef void *SDF_HANDLE;

/** \brief loads a SDFile to memory and returns a @SDF_HANDLE
  *
  * \param      filename    the filename to load, can be absolute or relative to the current working directory
  * \return                 to the loaded SDFile or 0 on error
  */
SDF_HANDLE BL_DLLIMPORT    SDF_open(const char *filename);

/** \brief closes a SDFile opened using @SDF_open
  *
  * \param      handle  the SDFile handle to close
  * \return             0 on success
  */
int BL_DLLIMPORT    SDF_close(SDF_HANDLE handle);

/** \brief download a SDFile to a BabyLIN device
 *
 * \param       sdfhandle   the SDFile from @SDF_open to download
 * \param       blhandle    the BabyLIN connection handle from @BLC_open to download to
 * \param       mode        see @BLC_loadSDF modes
 * \return                  see @BLC_loadSDF returncodes (0 = success)
 */
int BL_DLLIMPORT    SDF_downloadToDevice(SDF_HANDLE sdfhandle, BL_HANDLE blhandle, int mode);

/** \brief download a SDFile to a BabyLIN device
 *
 * \param       sectionhandle the SDFile from @SDF_open to download
 * \param       channelhandle the BabyLIN connection handle from @BLC_open to download to
 * \return                  see @BLC_loadSDF returncodes (0 = success)
 */
int BL_DLLIMPORT    SDF_downloadSectionToChannel(SDF_HANDLE sectionhandle, BL_HANDLE channelhandle);

/** \brief get number of sections in SDF
 *
 * \param       sectionhandle the SDFile from @SDF_open
 * \return      number of sections ( negative value on error )
 */
int BL_DLLIMPORT    SDF_getSectionCount(SDF_HANDLE sdfhandle);

/**
 * @brief SDF_getSectionHandle get handle to a section of a sdf
 * @param handle    the handle of the sdf to get the section handle from
 * @param sectionNr the section number to get the handle for
 * @return handle to the section ( 0 on error )
 */
SDF_HANDLE BL_DLLIMPORT    SDF_getSectionHandle(SDF_HANDLE handle, int sectionNr);

/**
 * @brief SDF_getSectionInfo get information about a section
 * @param handle the section handle to retrieve informations about
 * @param info pointer to pre-allocated SDF_SECTIONINFO structure to fill
 * @return 0 on success
 */
int BL_DLLIMPORT    SDF_getSectionInfo(SDF_HANDLE handle, SDF_SECTIONINFO *info);
/** @} */

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // SDF_H
