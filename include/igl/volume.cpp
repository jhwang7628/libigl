// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2014 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "volume.h"
#include "cross.h"
#include <Eigen/Geometry>
template <
  typename DerivedV, 
  typename DerivedT, 
  typename Derivedvol>
IGL_INLINE void igl::volume(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedT>& T,
  Eigen::PlainObjectBase<Derivedvol>& vol)
{
  using namespace Eigen;
  const int m = T.rows();
  vol.resize(m,1);
  for(int t = 0;t<m;t++)
  {
    const auto & a = V.row(T(t,0));
    const auto & b = V.row(T(t,1));
    const auto & c = V.row(T(t,2));
    const auto & d = V.row(T(t,3));
    vol(t) = -(a-d).dot((b-d).cross(c-d))/6.;
  }
}

template <
  typename DerivedA,
  typename DerivedB,
  typename DerivedC,
  typename DerivedD,
  typename Derivedvol>
IGL_INLINE void igl::volume(
  const Eigen::PlainObjectBase<DerivedA> & A,
  const Eigen::PlainObjectBase<DerivedB> & B,
  const Eigen::PlainObjectBase<DerivedC> & C,
  const Eigen::PlainObjectBase<DerivedD> & D,
  Eigen::PlainObjectBase<Derivedvol> & vol)
{
  const auto & AmD = A-D;
  const auto & BmD = B-D;
  const auto & CmD = C-D;
  Eigen::PlainObjectBase<DerivedA> BmDxCmD;
  cross(BmD.eval(),CmD.eval(),BmDxCmD);
  const auto & AmDdx = (AmD.array() * BmDxCmD.array()).rowwise().sum();
  vol = -AmDdx/6.;
}

template <
  typename VecA,
  typename VecB,
  typename VecC,
  typename VecD>
IGL_INLINE typename VecA::Scalar igl::volume_single(
  const VecA & a,
  const VecB & b,
  const VecC & c,
  const VecD & d)
{
  return -(a-d).dot((b-d).cross(c-d))/6.;
}


template <
  typename DerivedL, 
  typename Derivedvol>
IGL_INLINE void igl::volume(
  const Eigen::PlainObjectBase<DerivedL>& L,
  Eigen::PlainObjectBase<Derivedvol>& vol)
{
  using namespace Eigen;
  const int m = L.rows();
  typedef typename Derivedvol::Scalar ScalarS;
  vol.resize(m,1);
  for(int t = 0;t<m;t++)
  {
    const ScalarS u = L(t,0);
    const ScalarS v = L(t,1);
    const ScalarS w = L(t,2);
    const ScalarS U = L(t,3);
    const ScalarS V = L(t,4);
    const ScalarS W = L(t,5);
    const ScalarS X = (w - U + v)*(U + v + w);
    const ScalarS x = (U - v + w)*(v - w + U);
    const ScalarS Y = (u - V + w)*(V + w + u);
    const ScalarS y = (V - w + u)*(w - u + V);
    const ScalarS Z = (v - W + u)*(W + u + v);
    const ScalarS z = (W - u + v)*(u - v + W);
    const ScalarS a = sqrt(x*Y*Z); 
    const ScalarS b = sqrt(y*Z*X); 
    const ScalarS c = sqrt(z*X*Y); 
    const ScalarS d = sqrt(x*y*z); 
    vol(t) = sqrt(
       (-a + b + c + d)*
       ( a - b + c + d)*
       ( a + b - c + d)*
       ( a + b + c - d))/
       (192.*u*v*w);
  }
}
#ifdef IGL_STATIC_LIBRARY
// Explicit template specialization
// generated by autoexplicit.sh
template void igl::volume<Eigen::Matrix<double, -1, 6, 0, -1, 6>, Eigen::Matrix<double, -1, 1, 0, -1, 1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 6, 0, -1, 6> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 1, 0, -1, 1> >&);
template Eigen::Matrix<double, 1, 3, 1, 1, 3>::Scalar igl::volume_single<Eigen::Matrix<double, 1, 3, 1, 1, 3>, Eigen::Matrix<double, 1, 3, 1, 1, 3>, Eigen::Matrix<double, 1, 3, 1, 1, 3>, Eigen::Matrix<double, 1, 3, 1, 1, 3> >(Eigen::Matrix<double, 1, 3, 1, 1, 3> const&, Eigen::Matrix<double, 1, 3, 1, 1, 3> const&, Eigen::Matrix<double, 1, 3, 1, 1, 3> const&, Eigen::Matrix<double, 1, 3, 1, 1, 3> const&);
template Eigen::Matrix<double, 3, 1, 0, 3, 1>::Scalar igl::volume_single<Eigen::Matrix<double, 3, 1, 0, 3, 1>, Eigen::Matrix<double, 3, 1, 0, 3, 1>, Eigen::Matrix<double, 3, 1, 0, 3, 1>, Eigen::Matrix<double, 3, 1, 0, 3, 1> >(Eigen::Matrix<double, 3, 1, 0, 3, 1> const&, Eigen::Matrix<double, 3, 1, 0, 3, 1> const&, Eigen::Matrix<double, 3, 1, 0, 3, 1> const&, Eigen::Matrix<double, 3, 1, 0, 3, 1> const&);
template void igl::volume<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, 1, 0, -1, 1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 1, 0, -1, 1> >&);
#endif
