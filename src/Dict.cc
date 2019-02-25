// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "interface/AnalObjects.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TTStudycLcLEvent(void *p = 0);
   static void *newArray_TTStudycLcLEvent(Long_t size, void *p);
   static void delete_TTStudycLcLEvent(void *p);
   static void deleteArray_TTStudycLcLEvent(void *p);
   static void destruct_TTStudycLcLEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::Event*)
   {
      ::TTStudy::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::Event >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::Event", ::TTStudy::Event::Class_Version(), "AnalObjects.h", 12,
                  typeid(::TTStudy::Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::Event::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::Event) );
      instance.SetNew(&new_TTStudycLcLEvent);
      instance.SetNewArray(&newArray_TTStudycLcLEvent);
      instance.SetDelete(&delete_TTStudycLcLEvent);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLEvent);
      instance.SetDestructor(&destruct_TTStudycLcLEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::Event*)
   {
      return GenerateInitInstanceLocal((::TTStudy::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::Event*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTStudycLcLTracklet(void *p = 0);
   static void *newArray_TTStudycLcLTracklet(Long_t size, void *p);
   static void delete_TTStudycLcLTracklet(void *p);
   static void deleteArray_TTStudycLcLTracklet(void *p);
   static void destruct_TTStudycLcLTracklet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::Tracklet*)
   {
      ::TTStudy::Tracklet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::Tracklet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::Tracklet", ::TTStudy::Tracklet::Class_Version(), "AnalObjects.h", 38,
                  typeid(::TTStudy::Tracklet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::Tracklet::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::Tracklet) );
      instance.SetNew(&new_TTStudycLcLTracklet);
      instance.SetNewArray(&newArray_TTStudycLcLTracklet);
      instance.SetDelete(&delete_TTStudycLcLTracklet);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLTracklet);
      instance.SetDestructor(&destruct_TTStudycLcLTracklet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::Tracklet*)
   {
      return GenerateInitInstanceLocal((::TTStudy::Tracklet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::Tracklet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTStudycLcLElectron(void *p = 0);
   static void *newArray_TTStudycLcLElectron(Long_t size, void *p);
   static void delete_TTStudycLcLElectron(void *p);
   static void deleteArray_TTStudycLcLElectron(void *p);
   static void destruct_TTStudycLcLElectron(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::Electron*)
   {
      ::TTStudy::Electron *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::Electron >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::Electron", ::TTStudy::Electron::Class_Version(), "AnalObjects.h", 79,
                  typeid(::TTStudy::Electron), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::Electron::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::Electron) );
      instance.SetNew(&new_TTStudycLcLElectron);
      instance.SetNewArray(&newArray_TTStudycLcLElectron);
      instance.SetDelete(&delete_TTStudycLcLElectron);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLElectron);
      instance.SetDestructor(&destruct_TTStudycLcLElectron);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::Electron*)
   {
      return GenerateInitInstanceLocal((::TTStudy::Electron*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::Electron*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTStudycLcLSimTrack(void *p = 0);
   static void *newArray_TTStudycLcLSimTrack(Long_t size, void *p);
   static void delete_TTStudycLcLSimTrack(void *p);
   static void deleteArray_TTStudycLcLSimTrack(void *p);
   static void destruct_TTStudycLcLSimTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::SimTrack*)
   {
      ::TTStudy::SimTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::SimTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::SimTrack", ::TTStudy::SimTrack::Class_Version(), "AnalObjects.h", 104,
                  typeid(::TTStudy::SimTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::SimTrack::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::SimTrack) );
      instance.SetNew(&new_TTStudycLcLSimTrack);
      instance.SetNewArray(&newArray_TTStudycLcLSimTrack);
      instance.SetDelete(&delete_TTStudycLcLSimTrack);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLSimTrack);
      instance.SetDestructor(&destruct_TTStudycLcLSimTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::SimTrack*)
   {
      return GenerateInitInstanceLocal((::TTStudy::SimTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::SimTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTStudycLcLTrack(void *p = 0);
   static void *newArray_TTStudycLcLTrack(Long_t size, void *p);
   static void delete_TTStudycLcLTrack(void *p);
   static void deleteArray_TTStudycLcLTrack(void *p);
   static void destruct_TTStudycLcLTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::Track*)
   {
      ::TTStudy::Track *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::Track >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::Track", ::TTStudy::Track::Class_Version(), "AnalObjects.h", 122,
                  typeid(::TTStudy::Track), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::Track::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::Track) );
      instance.SetNew(&new_TTStudycLcLTrack);
      instance.SetNewArray(&newArray_TTStudycLcLTrack);
      instance.SetDelete(&delete_TTStudycLcLTrack);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLTrack);
      instance.SetDestructor(&destruct_TTStudycLcLTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::Track*)
   {
      return GenerateInitInstanceLocal((::TTStudy::Track*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::Track*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTStudycLcLGenParticle(void *p = 0);
   static void *newArray_TTStudycLcLGenParticle(Long_t size, void *p);
   static void delete_TTStudycLcLGenParticle(void *p);
   static void deleteArray_TTStudycLcLGenParticle(void *p);
   static void destruct_TTStudycLcLGenParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::GenParticle*)
   {
      ::TTStudy::GenParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::GenParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::GenParticle", ::TTStudy::GenParticle::Class_Version(), "AnalObjects.h", 169,
                  typeid(::TTStudy::GenParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::GenParticle::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::GenParticle) );
      instance.SetNew(&new_TTStudycLcLGenParticle);
      instance.SetNewArray(&newArray_TTStudycLcLGenParticle);
      instance.SetDelete(&delete_TTStudycLcLGenParticle);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLGenParticle);
      instance.SetDestructor(&destruct_TTStudycLcLGenParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::GenParticle*)
   {
      return GenerateInitInstanceLocal((::TTStudy::GenParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::GenParticle*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTStudycLcLL1Jet(void *p = 0);
   static void *newArray_TTStudycLcLL1Jet(Long_t size, void *p);
   static void delete_TTStudycLcLL1Jet(void *p);
   static void deleteArray_TTStudycLcLL1Jet(void *p);
   static void destruct_TTStudycLcLL1Jet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::L1Jet*)
   {
      ::TTStudy::L1Jet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::L1Jet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::L1Jet", ::TTStudy::L1Jet::Class_Version(), "AnalObjects.h", 194,
                  typeid(::TTStudy::L1Jet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::L1Jet::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::L1Jet) );
      instance.SetNew(&new_TTStudycLcLL1Jet);
      instance.SetNewArray(&newArray_TTStudycLcLL1Jet);
      instance.SetDelete(&delete_TTStudycLcLL1Jet);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLL1Jet);
      instance.SetDestructor(&destruct_TTStudycLcLL1Jet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::L1Jet*)
   {
      return GenerateInitInstanceLocal((::TTStudy::L1Jet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::L1Jet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TTStudycLcLL1Muon(void *p = 0);
   static void *newArray_TTStudycLcLL1Muon(Long_t size, void *p);
   static void delete_TTStudycLcLL1Muon(void *p);
   static void deleteArray_TTStudycLcLL1Muon(void *p);
   static void destruct_TTStudycLcLL1Muon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTStudy::L1Muon*)
   {
      ::TTStudy::L1Muon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTStudy::L1Muon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTStudy::L1Muon", ::TTStudy::L1Muon::Class_Version(), "AnalObjects.h", 209,
                  typeid(::TTStudy::L1Muon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTStudy::L1Muon::Dictionary, isa_proxy, 4,
                  sizeof(::TTStudy::L1Muon) );
      instance.SetNew(&new_TTStudycLcLL1Muon);
      instance.SetNewArray(&newArray_TTStudycLcLL1Muon);
      instance.SetDelete(&delete_TTStudycLcLL1Muon);
      instance.SetDeleteArray(&deleteArray_TTStudycLcLL1Muon);
      instance.SetDestructor(&destruct_TTStudycLcLL1Muon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTStudy::L1Muon*)
   {
      return GenerateInitInstanceLocal((::TTStudy::L1Muon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TTStudy::L1Muon*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr Event::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Event::Class_Name()
{
   return "TTStudy::Event";
}

//______________________________________________________________________________
const char *Event::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Event*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Event::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Event*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Event::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Event*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Event::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Event*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr Tracklet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Tracklet::Class_Name()
{
   return "TTStudy::Tracklet";
}

//______________________________________________________________________________
const char *Tracklet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Tracklet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Tracklet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Tracklet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Tracklet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Tracklet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Tracklet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Tracklet*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr Electron::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Electron::Class_Name()
{
   return "TTStudy::Electron";
}

//______________________________________________________________________________
const char *Electron::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Electron*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Electron::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Electron*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Electron::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Electron*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Electron::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Electron*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr SimTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SimTrack::Class_Name()
{
   return "TTStudy::SimTrack";
}

//______________________________________________________________________________
const char *SimTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::SimTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SimTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::SimTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SimTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::SimTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SimTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::SimTrack*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr Track::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Track::Class_Name()
{
   return "TTStudy::Track";
}

//______________________________________________________________________________
const char *Track::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Track*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Track::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Track*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Track::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Track*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Track::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::Track*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr GenParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *GenParticle::Class_Name()
{
   return "TTStudy::GenParticle";
}

//______________________________________________________________________________
const char *GenParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::GenParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int GenParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::GenParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *GenParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::GenParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *GenParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::GenParticle*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr L1Jet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *L1Jet::Class_Name()
{
   return "TTStudy::L1Jet";
}

//______________________________________________________________________________
const char *L1Jet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Jet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int L1Jet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Jet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *L1Jet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Jet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *L1Jet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Jet*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
atomic_TClass_ptr L1Muon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *L1Muon::Class_Name()
{
   return "TTStudy::L1Muon";
}

//______________________________________________________________________________
const char *L1Muon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Muon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int L1Muon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Muon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *L1Muon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Muon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *L1Muon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTStudy::L1Muon*)0x0)->GetClass(); }
   return fgIsA;
}

} // namespace TTStudy
namespace TTStudy {
//______________________________________________________________________________
void Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::Event.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::Event::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::Event::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLEvent(void *p) {
      return  p ? new(p) ::TTStudy::Event : new ::TTStudy::Event;
   }
   static void *newArray_TTStudycLcLEvent(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::Event[nElements] : new ::TTStudy::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLEvent(void *p) {
      delete ((::TTStudy::Event*)p);
   }
   static void deleteArray_TTStudycLcLEvent(void *p) {
      delete [] ((::TTStudy::Event*)p);
   }
   static void destruct_TTStudycLcLEvent(void *p) {
      typedef ::TTStudy::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::Event

namespace TTStudy {
//______________________________________________________________________________
void Tracklet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::Tracklet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::Tracklet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::Tracklet::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLTracklet(void *p) {
      return  p ? new(p) ::TTStudy::Tracklet : new ::TTStudy::Tracklet;
   }
   static void *newArray_TTStudycLcLTracklet(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::Tracklet[nElements] : new ::TTStudy::Tracklet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLTracklet(void *p) {
      delete ((::TTStudy::Tracklet*)p);
   }
   static void deleteArray_TTStudycLcLTracklet(void *p) {
      delete [] ((::TTStudy::Tracklet*)p);
   }
   static void destruct_TTStudycLcLTracklet(void *p) {
      typedef ::TTStudy::Tracklet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::Tracklet

namespace TTStudy {
//______________________________________________________________________________
void Electron::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::Electron.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::Electron::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::Electron::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLElectron(void *p) {
      return  p ? new(p) ::TTStudy::Electron : new ::TTStudy::Electron;
   }
   static void *newArray_TTStudycLcLElectron(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::Electron[nElements] : new ::TTStudy::Electron[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLElectron(void *p) {
      delete ((::TTStudy::Electron*)p);
   }
   static void deleteArray_TTStudycLcLElectron(void *p) {
      delete [] ((::TTStudy::Electron*)p);
   }
   static void destruct_TTStudycLcLElectron(void *p) {
      typedef ::TTStudy::Electron current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::Electron

namespace TTStudy {
//______________________________________________________________________________
void SimTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::SimTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::SimTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::SimTrack::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLSimTrack(void *p) {
      return  p ? new(p) ::TTStudy::SimTrack : new ::TTStudy::SimTrack;
   }
   static void *newArray_TTStudycLcLSimTrack(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::SimTrack[nElements] : new ::TTStudy::SimTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLSimTrack(void *p) {
      delete ((::TTStudy::SimTrack*)p);
   }
   static void deleteArray_TTStudycLcLSimTrack(void *p) {
      delete [] ((::TTStudy::SimTrack*)p);
   }
   static void destruct_TTStudycLcLSimTrack(void *p) {
      typedef ::TTStudy::SimTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::SimTrack

namespace TTStudy {
//______________________________________________________________________________
void Track::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::Track.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::Track::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::Track::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLTrack(void *p) {
      return  p ? new(p) ::TTStudy::Track : new ::TTStudy::Track;
   }
   static void *newArray_TTStudycLcLTrack(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::Track[nElements] : new ::TTStudy::Track[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLTrack(void *p) {
      delete ((::TTStudy::Track*)p);
   }
   static void deleteArray_TTStudycLcLTrack(void *p) {
      delete [] ((::TTStudy::Track*)p);
   }
   static void destruct_TTStudycLcLTrack(void *p) {
      typedef ::TTStudy::Track current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::Track

namespace TTStudy {
//______________________________________________________________________________
void GenParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::GenParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::GenParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::GenParticle::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLGenParticle(void *p) {
      return  p ? new(p) ::TTStudy::GenParticle : new ::TTStudy::GenParticle;
   }
   static void *newArray_TTStudycLcLGenParticle(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::GenParticle[nElements] : new ::TTStudy::GenParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLGenParticle(void *p) {
      delete ((::TTStudy::GenParticle*)p);
   }
   static void deleteArray_TTStudycLcLGenParticle(void *p) {
      delete [] ((::TTStudy::GenParticle*)p);
   }
   static void destruct_TTStudycLcLGenParticle(void *p) {
      typedef ::TTStudy::GenParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::GenParticle

namespace TTStudy {
//______________________________________________________________________________
void L1Jet::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::L1Jet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::L1Jet::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::L1Jet::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLL1Jet(void *p) {
      return  p ? new(p) ::TTStudy::L1Jet : new ::TTStudy::L1Jet;
   }
   static void *newArray_TTStudycLcLL1Jet(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::L1Jet[nElements] : new ::TTStudy::L1Jet[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLL1Jet(void *p) {
      delete ((::TTStudy::L1Jet*)p);
   }
   static void deleteArray_TTStudycLcLL1Jet(void *p) {
      delete [] ((::TTStudy::L1Jet*)p);
   }
   static void destruct_TTStudycLcLL1Jet(void *p) {
      typedef ::TTStudy::L1Jet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::L1Jet

namespace TTStudy {
//______________________________________________________________________________
void L1Muon::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTStudy::L1Muon.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TTStudy::L1Muon::Class(),this);
   } else {
      R__b.WriteClassBuffer(TTStudy::L1Muon::Class(),this);
   }
}

} // namespace TTStudy
namespace ROOT {
   // Wrappers around operator new
   static void *new_TTStudycLcLL1Muon(void *p) {
      return  p ? new(p) ::TTStudy::L1Muon : new ::TTStudy::L1Muon;
   }
   static void *newArray_TTStudycLcLL1Muon(Long_t nElements, void *p) {
      return p ? new(p) ::TTStudy::L1Muon[nElements] : new ::TTStudy::L1Muon[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTStudycLcLL1Muon(void *p) {
      delete ((::TTStudy::L1Muon*)p);
   }
   static void deleteArray_TTStudycLcLL1Muon(void *p) {
      delete [] ((::TTStudy::L1Muon*)p);
   }
   static void destruct_TTStudycLcLL1Muon(void *p) {
      typedef ::TTStudy::L1Muon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TTStudy::L1Muon

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 214,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlETTStudycLcLTrackletgR_Dictionary();
   static void vectorlETTStudycLcLTrackletgR_TClassManip(TClass*);
   static void *new_vectorlETTStudycLcLTrackletgR(void *p = 0);
   static void *newArray_vectorlETTStudycLcLTrackletgR(Long_t size, void *p);
   static void delete_vectorlETTStudycLcLTrackletgR(void *p);
   static void deleteArray_vectorlETTStudycLcLTrackletgR(void *p);
   static void destruct_vectorlETTStudycLcLTrackletgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TTStudy::Tracklet>*)
   {
      vector<TTStudy::Tracklet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TTStudy::Tracklet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TTStudy::Tracklet>", -2, "vector", 214,
                  typeid(vector<TTStudy::Tracklet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTStudycLcLTrackletgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TTStudy::Tracklet>) );
      instance.SetNew(&new_vectorlETTStudycLcLTrackletgR);
      instance.SetNewArray(&newArray_vectorlETTStudycLcLTrackletgR);
      instance.SetDelete(&delete_vectorlETTStudycLcLTrackletgR);
      instance.SetDeleteArray(&deleteArray_vectorlETTStudycLcLTrackletgR);
      instance.SetDestructor(&destruct_vectorlETTStudycLcLTrackletgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TTStudy::Tracklet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TTStudy::Tracklet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTStudycLcLTrackletgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TTStudy::Tracklet>*)0x0)->GetClass();
      vectorlETTStudycLcLTrackletgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTStudycLcLTrackletgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTStudycLcLTrackletgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::Tracklet> : new vector<TTStudy::Tracklet>;
   }
   static void *newArray_vectorlETTStudycLcLTrackletgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::Tracklet>[nElements] : new vector<TTStudy::Tracklet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTStudycLcLTrackletgR(void *p) {
      delete ((vector<TTStudy::Tracklet>*)p);
   }
   static void deleteArray_vectorlETTStudycLcLTrackletgR(void *p) {
      delete [] ((vector<TTStudy::Tracklet>*)p);
   }
   static void destruct_vectorlETTStudycLcLTrackletgR(void *p) {
      typedef vector<TTStudy::Tracklet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TTStudy::Tracklet>

namespace ROOT {
   static TClass *vectorlETTStudycLcLTrackgR_Dictionary();
   static void vectorlETTStudycLcLTrackgR_TClassManip(TClass*);
   static void *new_vectorlETTStudycLcLTrackgR(void *p = 0);
   static void *newArray_vectorlETTStudycLcLTrackgR(Long_t size, void *p);
   static void delete_vectorlETTStudycLcLTrackgR(void *p);
   static void deleteArray_vectorlETTStudycLcLTrackgR(void *p);
   static void destruct_vectorlETTStudycLcLTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TTStudy::Track>*)
   {
      vector<TTStudy::Track> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TTStudy::Track>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TTStudy::Track>", -2, "vector", 214,
                  typeid(vector<TTStudy::Track>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTStudycLcLTrackgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TTStudy::Track>) );
      instance.SetNew(&new_vectorlETTStudycLcLTrackgR);
      instance.SetNewArray(&newArray_vectorlETTStudycLcLTrackgR);
      instance.SetDelete(&delete_vectorlETTStudycLcLTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlETTStudycLcLTrackgR);
      instance.SetDestructor(&destruct_vectorlETTStudycLcLTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TTStudy::Track> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TTStudy::Track>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTStudycLcLTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TTStudy::Track>*)0x0)->GetClass();
      vectorlETTStudycLcLTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTStudycLcLTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTStudycLcLTrackgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::Track> : new vector<TTStudy::Track>;
   }
   static void *newArray_vectorlETTStudycLcLTrackgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::Track>[nElements] : new vector<TTStudy::Track>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTStudycLcLTrackgR(void *p) {
      delete ((vector<TTStudy::Track>*)p);
   }
   static void deleteArray_vectorlETTStudycLcLTrackgR(void *p) {
      delete [] ((vector<TTStudy::Track>*)p);
   }
   static void destruct_vectorlETTStudycLcLTrackgR(void *p) {
      typedef vector<TTStudy::Track> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TTStudy::Track>

namespace ROOT {
   static TClass *vectorlETTStudycLcLSimTrackgR_Dictionary();
   static void vectorlETTStudycLcLSimTrackgR_TClassManip(TClass*);
   static void *new_vectorlETTStudycLcLSimTrackgR(void *p = 0);
   static void *newArray_vectorlETTStudycLcLSimTrackgR(Long_t size, void *p);
   static void delete_vectorlETTStudycLcLSimTrackgR(void *p);
   static void deleteArray_vectorlETTStudycLcLSimTrackgR(void *p);
   static void destruct_vectorlETTStudycLcLSimTrackgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TTStudy::SimTrack>*)
   {
      vector<TTStudy::SimTrack> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TTStudy::SimTrack>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TTStudy::SimTrack>", -2, "vector", 214,
                  typeid(vector<TTStudy::SimTrack>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTStudycLcLSimTrackgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TTStudy::SimTrack>) );
      instance.SetNew(&new_vectorlETTStudycLcLSimTrackgR);
      instance.SetNewArray(&newArray_vectorlETTStudycLcLSimTrackgR);
      instance.SetDelete(&delete_vectorlETTStudycLcLSimTrackgR);
      instance.SetDeleteArray(&deleteArray_vectorlETTStudycLcLSimTrackgR);
      instance.SetDestructor(&destruct_vectorlETTStudycLcLSimTrackgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TTStudy::SimTrack> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TTStudy::SimTrack>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTStudycLcLSimTrackgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TTStudy::SimTrack>*)0x0)->GetClass();
      vectorlETTStudycLcLSimTrackgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTStudycLcLSimTrackgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTStudycLcLSimTrackgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::SimTrack> : new vector<TTStudy::SimTrack>;
   }
   static void *newArray_vectorlETTStudycLcLSimTrackgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::SimTrack>[nElements] : new vector<TTStudy::SimTrack>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTStudycLcLSimTrackgR(void *p) {
      delete ((vector<TTStudy::SimTrack>*)p);
   }
   static void deleteArray_vectorlETTStudycLcLSimTrackgR(void *p) {
      delete [] ((vector<TTStudy::SimTrack>*)p);
   }
   static void destruct_vectorlETTStudycLcLSimTrackgR(void *p) {
      typedef vector<TTStudy::SimTrack> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TTStudy::SimTrack>

namespace ROOT {
   static TClass *vectorlETTStudycLcLL1MuongR_Dictionary();
   static void vectorlETTStudycLcLL1MuongR_TClassManip(TClass*);
   static void *new_vectorlETTStudycLcLL1MuongR(void *p = 0);
   static void *newArray_vectorlETTStudycLcLL1MuongR(Long_t size, void *p);
   static void delete_vectorlETTStudycLcLL1MuongR(void *p);
   static void deleteArray_vectorlETTStudycLcLL1MuongR(void *p);
   static void destruct_vectorlETTStudycLcLL1MuongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TTStudy::L1Muon>*)
   {
      vector<TTStudy::L1Muon> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TTStudy::L1Muon>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TTStudy::L1Muon>", -2, "vector", 214,
                  typeid(vector<TTStudy::L1Muon>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTStudycLcLL1MuongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TTStudy::L1Muon>) );
      instance.SetNew(&new_vectorlETTStudycLcLL1MuongR);
      instance.SetNewArray(&newArray_vectorlETTStudycLcLL1MuongR);
      instance.SetDelete(&delete_vectorlETTStudycLcLL1MuongR);
      instance.SetDeleteArray(&deleteArray_vectorlETTStudycLcLL1MuongR);
      instance.SetDestructor(&destruct_vectorlETTStudycLcLL1MuongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TTStudy::L1Muon> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TTStudy::L1Muon>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTStudycLcLL1MuongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TTStudy::L1Muon>*)0x0)->GetClass();
      vectorlETTStudycLcLL1MuongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTStudycLcLL1MuongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTStudycLcLL1MuongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::L1Muon> : new vector<TTStudy::L1Muon>;
   }
   static void *newArray_vectorlETTStudycLcLL1MuongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::L1Muon>[nElements] : new vector<TTStudy::L1Muon>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTStudycLcLL1MuongR(void *p) {
      delete ((vector<TTStudy::L1Muon>*)p);
   }
   static void deleteArray_vectorlETTStudycLcLL1MuongR(void *p) {
      delete [] ((vector<TTStudy::L1Muon>*)p);
   }
   static void destruct_vectorlETTStudycLcLL1MuongR(void *p) {
      typedef vector<TTStudy::L1Muon> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TTStudy::L1Muon>

namespace ROOT {
   static TClass *vectorlETTStudycLcLL1JetgR_Dictionary();
   static void vectorlETTStudycLcLL1JetgR_TClassManip(TClass*);
   static void *new_vectorlETTStudycLcLL1JetgR(void *p = 0);
   static void *newArray_vectorlETTStudycLcLL1JetgR(Long_t size, void *p);
   static void delete_vectorlETTStudycLcLL1JetgR(void *p);
   static void deleteArray_vectorlETTStudycLcLL1JetgR(void *p);
   static void destruct_vectorlETTStudycLcLL1JetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TTStudy::L1Jet>*)
   {
      vector<TTStudy::L1Jet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TTStudy::L1Jet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TTStudy::L1Jet>", -2, "vector", 214,
                  typeid(vector<TTStudy::L1Jet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTStudycLcLL1JetgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TTStudy::L1Jet>) );
      instance.SetNew(&new_vectorlETTStudycLcLL1JetgR);
      instance.SetNewArray(&newArray_vectorlETTStudycLcLL1JetgR);
      instance.SetDelete(&delete_vectorlETTStudycLcLL1JetgR);
      instance.SetDeleteArray(&deleteArray_vectorlETTStudycLcLL1JetgR);
      instance.SetDestructor(&destruct_vectorlETTStudycLcLL1JetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TTStudy::L1Jet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TTStudy::L1Jet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTStudycLcLL1JetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TTStudy::L1Jet>*)0x0)->GetClass();
      vectorlETTStudycLcLL1JetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTStudycLcLL1JetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTStudycLcLL1JetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::L1Jet> : new vector<TTStudy::L1Jet>;
   }
   static void *newArray_vectorlETTStudycLcLL1JetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::L1Jet>[nElements] : new vector<TTStudy::L1Jet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTStudycLcLL1JetgR(void *p) {
      delete ((vector<TTStudy::L1Jet>*)p);
   }
   static void deleteArray_vectorlETTStudycLcLL1JetgR(void *p) {
      delete [] ((vector<TTStudy::L1Jet>*)p);
   }
   static void destruct_vectorlETTStudycLcLL1JetgR(void *p) {
      typedef vector<TTStudy::L1Jet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TTStudy::L1Jet>

namespace ROOT {
   static TClass *vectorlETTStudycLcLGenParticlegR_Dictionary();
   static void vectorlETTStudycLcLGenParticlegR_TClassManip(TClass*);
   static void *new_vectorlETTStudycLcLGenParticlegR(void *p = 0);
   static void *newArray_vectorlETTStudycLcLGenParticlegR(Long_t size, void *p);
   static void delete_vectorlETTStudycLcLGenParticlegR(void *p);
   static void deleteArray_vectorlETTStudycLcLGenParticlegR(void *p);
   static void destruct_vectorlETTStudycLcLGenParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TTStudy::GenParticle>*)
   {
      vector<TTStudy::GenParticle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TTStudy::GenParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TTStudy::GenParticle>", -2, "vector", 214,
                  typeid(vector<TTStudy::GenParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTStudycLcLGenParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TTStudy::GenParticle>) );
      instance.SetNew(&new_vectorlETTStudycLcLGenParticlegR);
      instance.SetNewArray(&newArray_vectorlETTStudycLcLGenParticlegR);
      instance.SetDelete(&delete_vectorlETTStudycLcLGenParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlETTStudycLcLGenParticlegR);
      instance.SetDestructor(&destruct_vectorlETTStudycLcLGenParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TTStudy::GenParticle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TTStudy::GenParticle>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTStudycLcLGenParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TTStudy::GenParticle>*)0x0)->GetClass();
      vectorlETTStudycLcLGenParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTStudycLcLGenParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTStudycLcLGenParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::GenParticle> : new vector<TTStudy::GenParticle>;
   }
   static void *newArray_vectorlETTStudycLcLGenParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::GenParticle>[nElements] : new vector<TTStudy::GenParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTStudycLcLGenParticlegR(void *p) {
      delete ((vector<TTStudy::GenParticle>*)p);
   }
   static void deleteArray_vectorlETTStudycLcLGenParticlegR(void *p) {
      delete [] ((vector<TTStudy::GenParticle>*)p);
   }
   static void destruct_vectorlETTStudycLcLGenParticlegR(void *p) {
      typedef vector<TTStudy::GenParticle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TTStudy::GenParticle>

namespace ROOT {
   static TClass *vectorlETTStudycLcLElectrongR_Dictionary();
   static void vectorlETTStudycLcLElectrongR_TClassManip(TClass*);
   static void *new_vectorlETTStudycLcLElectrongR(void *p = 0);
   static void *newArray_vectorlETTStudycLcLElectrongR(Long_t size, void *p);
   static void delete_vectorlETTStudycLcLElectrongR(void *p);
   static void deleteArray_vectorlETTStudycLcLElectrongR(void *p);
   static void destruct_vectorlETTStudycLcLElectrongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TTStudy::Electron>*)
   {
      vector<TTStudy::Electron> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TTStudy::Electron>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TTStudy::Electron>", -2, "vector", 214,
                  typeid(vector<TTStudy::Electron>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETTStudycLcLElectrongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TTStudy::Electron>) );
      instance.SetNew(&new_vectorlETTStudycLcLElectrongR);
      instance.SetNewArray(&newArray_vectorlETTStudycLcLElectrongR);
      instance.SetDelete(&delete_vectorlETTStudycLcLElectrongR);
      instance.SetDeleteArray(&deleteArray_vectorlETTStudycLcLElectrongR);
      instance.SetDestructor(&destruct_vectorlETTStudycLcLElectrongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TTStudy::Electron> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TTStudy::Electron>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETTStudycLcLElectrongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TTStudy::Electron>*)0x0)->GetClass();
      vectorlETTStudycLcLElectrongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETTStudycLcLElectrongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETTStudycLcLElectrongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::Electron> : new vector<TTStudy::Electron>;
   }
   static void *newArray_vectorlETTStudycLcLElectrongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TTStudy::Electron>[nElements] : new vector<TTStudy::Electron>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETTStudycLcLElectrongR(void *p) {
      delete ((vector<TTStudy::Electron>*)p);
   }
   static void deleteArray_vectorlETTStudycLcLElectrongR(void *p) {
      delete [] ((vector<TTStudy::Electron>*)p);
   }
   static void destruct_vectorlETTStudycLcLElectrongR(void *p) {
      typedef vector<TTStudy::Electron> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TTStudy::Electron>

namespace {
  void TriggerDictionaryInitialization_Dict_Impl() {
    static const char* headers[] = {
"interface/AnalObjects.h",
0
    };
    static const char* includePaths[] = {
"./interface",
"./",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc630/lcg/root/6.08.04-oenich/include",
"/afs/cern.ch/work/r/rbhattac/public/BsAnalysis_code_Apr17/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  Tracklet;}
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  L1Muon;}
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  L1Jet;}
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  GenParticle;}
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  Track;}
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  SimTrack;}
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  Electron;}
namespace TTStudy{class __attribute__((annotate("$clingAutoload$AnalObjects.h")))  Event;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "interface/AnalObjects.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TTStudy::Electron", payloadCode, "@",
"TTStudy::Event", payloadCode, "@",
"TTStudy::GenParticle", payloadCode, "@",
"TTStudy::L1Jet", payloadCode, "@",
"TTStudy::L1Muon", payloadCode, "@",
"TTStudy::SimTrack", payloadCode, "@",
"TTStudy::Track", payloadCode, "@",
"TTStudy::Tracklet", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dict() {
  TriggerDictionaryInitialization_Dict_Impl();
}
