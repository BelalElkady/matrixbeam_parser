#ifndef BABYLINSDF_H
#define BABYLINSDF_H

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
typedef const char *CPCHAR;

#endif
#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup l_sdf_functions Legacy SDF handling
 *  \brief List of legacy SDF functions
 *
 *  The following structures are used to retrieve data from a SDF loaded to a BabyLIN
 *  As these functions requeire a loaded SDF onto a BabyLIN, a existing connection to a BabyLIN is mendatory.
 *  Please see the new SDF API in @sdf_functions on how to handle SDFs without a BabyLIN connection
 *  @{
 */

// ! Get the SDF's number for node by name.
/*!
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param name     Name of the node.
 *  \return         Returns the node's number or -1 if there's no signal with
 *                  specified name. Even smaller numbers designate error codes
 *                  as defined in BabyLIN.h.
 */
int BL_DLLIMPORT   BL_SDF_getNodeNr(BL_HANDLE handle, const char *name);

// ! Get the SDF's number for signal by name.
/*!
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param name     Name of the signal.
 *  \return         Returns the signal's number or -1 if there's no signal with
 *                  specified name. Even smaller numbers designate error codes
 *                  as defined in BabyLIN.h.
 */
int BL_DLLIMPORT   BL_SDF_getSignalNr(BL_HANDLE handle, const char *name);

// ! Get the SDF's number for frame by name.
/*!
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param name     Name of the frame.
 *  \return         Returns the frame's number or -1 if there's no frame with
 *                  specified name. Even smaller numbers designate error codes
 *                  as defined in BabyLIN.h.
 */
int BL_DLLIMPORT   BL_SDF_getFrameNr(BL_HANDLE handle, const char *name);

// ! Get the SDF's number for schedule by name.
/*!
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param name     Name of the schedule.
 *  \return         Returns the schedule's number or -1 if there's no schedule with
 *                  specified name. Even smaller numbers designate error codes
 *                  as defined in BabyLIN.h.
 */
int BL_DLLIMPORT   BL_SDF_getScheduleNr(BL_HANDLE handle, const char *name);

// ! Get the number of schedule tables in the SDF.
/*!
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \return         Returns the number of schedule tablesname or 0 if there's no
 *                  schedule defined.
 */
int BL_DLLIMPORT   BL_SDF_getNumSchedules(BL_HANDLE handle);

// ! Get the SDF's name of schedule by number.
/*!
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param schedule_nr Index of the schedule.
 *  \return         Returns the schedule's name or empty string if there's no
 *                  schedule with specified index.
 */
CPCHAR BL_DLLIMPORT   BL_SDF_getScheduleName(BL_HANDLE handle, int schedule_nr);

// ! Get the SDF's number for macro by name.
/*!
 *  \param handle   Handle representing the connection; returned previously by
 *                  BL_open().
 *  \param name     Name of the macro.
 *  \return         Returns the macro's number or -1 if there's no macro with
 *                  specified name. Even smaller numbers designate error codes
 *                  as defined in BabyLIN.h.
 */
int BL_DLLIMPORT   BL_SDF_getMacroNr(BL_HANDLE handle, const char *name);

/** @} */

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // BABYLINSDF_H
