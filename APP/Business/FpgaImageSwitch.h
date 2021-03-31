/*
 * =====================================================================================
 *
 *       Filename:  FpgaImageSwitch.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2015年04月09日 22时40分20秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zt (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef  FPGAIMAGESWICTH_INC
#define  FPGAIMAGESWICTH_INC

#include <map>
#include <memory>
#include <pthread.h>

#include "FpgaImageHandle.h"

typedef std::shared_ptr<FpgaImageHandle> ( *pGetFpgaImageHandleObj ) ( );
typedef std::map<int, pGetFpgaImageHandleObj> mapGetFpgaImageHandleObj_t;

class FpgaImageSwitch
{
  private:
    FpgaImageSwitch();
    ~FpgaImageSwitch();

  public:
    static std::shared_ptr<FpgaImageHandle> GetObj ( int index );
    static bool SetDeskTopIndex ( uint32_t index );
    static int GetDeskTopIndex ( );

  private:
    static mapGetFpgaImageHandleObj_t m_mapGetFpgaImageHandleObj;
};

#endif   /* ----- #ifndef FpgaImageSwitch.h ----- */

