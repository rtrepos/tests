/**
  * @file EDED.cpp
  * @author ...
  * @@tagdynamic@@
  * @@tagdepends:vle.extension.differential-equation,vle.extension.difference-equation@@endtagdepends
  * @@tag DifferenceEquationMultiple@vle.extension.difference-equation @@namespace:pkgNewCmake;class:EDED;par:;sync:;nosync:@@end tag@@
  */

#include <vle/extension/DifferenceEquation.hpp>

//@@begin:includes@@
//@@end:includes@@

namespace vd = vle::devs;
namespace ve = vle::extension;
namespace vv = vle::value;

namespace pkgNewCmake {

class EDED : public ve::DifferenceEquation::Multiple
{
public:
    EDED(
       const vd::DynamicsInit& atom,
       const vd::InitEventList& evts)
        : ve::DifferenceEquation::Multiple(atom, evts)
    {
        A = createVar("A");
    }

    virtual ~EDED()
    {}

//@@begin:compute@@
virtual void compute(const vd::Time& /*time*/)
{ }
//@@end:compute@@

//@@begin:initValue@@
virtual void initValue(const vd::Time& /*time*/)
{ }
//@@end:initValue@@

private:
//@@begin:user@@
//@@end:user@@

    Var A;
};

} // namespace pkgNewCmake

DECLARE_DYNAMICS(pkgNewCmake::EDED)

