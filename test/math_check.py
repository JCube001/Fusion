#!/usr/bin/env python3
#
# This script helps to verify that this library's math is equivalent to the math
# in the AHRS article by Sebastian O.H. Madgwick.
#
# Note: All tuples must be normalized.
#

from math import *

# Quaternion cross product
def q_cross(a, b):
    return (a[0]*b[0] - a[1]*b[1] - a[2]*b[2] - a[3]*b[3],
            a[0]*b[1] + a[1]*b[0] + a[2]*b[3] - a[3]*b[2],
            a[0]*b[2] - a[1]*b[3] + a[2]*b[0] + a[3]*b[1],
            a[0]*b[3] + a[1]*b[2] - a[2]*b[1] + a[3]*b[0])

# Quaternion norm
def q_norm(q):
  return sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3])

# Quaternion normalize
def q_normalize(q):
  n = q_norm(q)
  return (q[0] / n, q[1] / n, q[2] / n, q[3] / n)

# Accelerometer objective function (our quaternion version)
def f_g_1(SEq, Eg, Sa):
    SEqq = (SEq[0], -SEq[1], -SEq[2], -SEq[3])
    q_tmp = q_cross(q_cross(SEqq, Eg), SEq)
    
    return (q_tmp[1] - Sa[1], q_tmp[2] - Sa[2], q_tmp[3] - Sa[3])

# Accelerometer objective function (article's matrix version)
def f_g_2(SEq, Sa):
    q1 = SEq[0]
    q2 = SEq[1]
    q3 = SEq[2]
    q4 = SEq[3]
    
    ax = Sa[1]
    ay = Sa[2]
    az = Sa[3]
    
    return (2.0*(q2*q4 - q1*q3) - ax,
            2.0*(q1*q2 + q3*q4) - ay,
            2.0*(0.5 - q2*q2 - q3*q3) - az)

# Accelerometer objective function's Jacobian matrix
def J_g(SEq):
    q1 = SEq[0]
    q2 = SEq[1]
    q3 = SEq[2]
    q4 = SEq[3]
    
    return ((-2.0*q3, 2.0*q4, -2.0*q1, 2.0*q2),
            (2.0*q2, 2.0*q1, 2.0*q4, 2.0*q3),
            (0.0, -4.0*q2, -4.0*q3, 0.0))

# Accelerometer descent gradient (our quaternion version)
def d_f_1(J, f):
    JT_11 = J[0][0]
    JT_12 = J[1][0]
    JT_13 = J[2][0]
    JT_21 = J[0][1]
    JT_22 = J[1][1]
    JT_23 = J[2][1]
    JT_31 = J[0][2]
    JT_32 = J[1][2]
    JT_33 = J[2][2]
    JT_41 = J[0][3]
    JT_42 = J[1][3]
    JT_43 = J[2][3]
    
    f_1 = f[0]
    f_2 = f[1]
    f_3 = f[2]
    
    return (JT_11*f_1 + JT_12*f_2 + JT_13*f_3,
            JT_21*f_1 + JT_22*f_2 + JT_23*f_3,
            JT_31*f_1 + JT_32*f_2 + JT_33*f_3,
            JT_41*f_1 + JT_42*f_2 + JT_43*f_3)

# Accelerometer descent gradient (article's matrix version)
def d_f_2(J, f):
    J_11 = J[0][0]
    J_12 = J[0][1]
    J_13 = J[0][2]
    J_14 = J[0][3]
    J_32 = J[2][1]
    J_33 = J[2][2]
    
    f_1 = f[0]
    f_2 = f[1]
    f_3 = f[2]
    
    return (J_14*f_2 - J_11*f_1,
            J_12*f_1 + J_13*f_2 - J_32*f_3,
            J_12*f_2 - J_33*f_3 - J_13*f_1,
            J_14*f_1 + J_11*f_2)

# Globals shared by update functions
deltat = 0.001
gyroMeasError = pi * (5.0 / 180.0)
beta = sqrt(3.0 / 4.0) * gyroMeasError
SEq_1 = 1.0
SEq_2 = 0.0
SEq_3 = 0.0
SEq_4 = 0.0

# My accelerometer and gyroscope update
def update_1(wx, wy, wz, ax, ay, az):
    pass

# Article's accelerometer and gyroscope update
def update_2(w_x, w_y, w_z, a_x, a_y, a_z):
    global deltat
    global beta
    global SEq_1
    global SEq_2
    global SEq_3
    global SEq_4
    
    # Local variables
    norm = 0.0
    SEqDot_omega_1 = 0.0
    SEqDot_omega_2 = 0.0
    SEqDot_omega_3 = 0.0
    SEqDot_omega_4 = 0.0
    f_1 = 0.0
    f_2 = 0.0
    f_3 = 0.0
    J_11or24 = 0.0
    J_12or23 = 0.0
    J_13or22 = 0.0
    J_14or21 = 0.0
    J_32 = 0.0
    J_33 = 0.0
    SEqHatDot_1 = 0.0
    SEqHatDot_2 = 0.0
    SEqHatDot_3 = 0.0
    SEqHatDot_4 = 0.0

    # Auxiliary variables
    halfSEq_1 = 0.5 * SEq_1
    halfSEq_2 = 0.5 * SEq_2
    halfSEq_3 = 0.5 * SEq_3
    halfSEq_4 = 0.5 * SEq_4
    twoSEq_1 = 2.0 * SEq_1
    twoSEq_2 = 2.0 * SEq_2
    twoSEq_3 = 2.0 * SEq_3
    twoSEq_4 = 2.0 * SEq_4

    # Normalize the accelerometer measurements
    norm = sqrt(a_x * a_x + a_y * a_y + a_z * a_z)
    a_x /= norm
    a_y /= norm
    a_z /= norm

    # Compute the objective function and Jacobian
    f_1 = twoSEq_2 * SEq_4 - twoSEq_1 * SEq_3 - a_x
    f_2 = twoSEq_1 * SEq_2 + twoSEq_3 * SEq_4 - a_y
    f_3 = 1.0 - twoSEq_2 * SEq_2 - twoSEq_3 * SEq_3 - a_z
    J_11or24 = twoSEq_3
    J_12or23 = 2.0 * SEq_4
    J_13or22 = twoSEq_1
    J_14or21 = twoSEq_2
    J_32 = 2.0 * J_14or21
    J_33 = 2.0 * J_11or24

    # Compute the gradient (matrix multiplication)
    SEqHatDot_1 = J_14or21 * f_2 - J_11or24 * f_1
    SEqHatDot_2 = J_12or23 * f_1 + J_13or22 * f_2 - J_32 * f_3
    SEqHatDot_3 = J_12or23 * f_2 - J_33 * f_3 - J_13or22 * f_1
    SEqHatDot_4 = J_14or21 * f_1 + J_11or24 * f_2

    # Normalize the gradient
    norm = sqrt(SEqHatDot_1 * SEqHatDot_1 + SEqHatDot_2 * SEqHatDot_2 +
              SEqHatDot_3 * SEqHatDot_3 + SEqHatDot_4 * SEqHatDot_4)
    SEqHatDot_1 /= norm
    SEqHatDot_2 /= norm
    SEqHatDot_3 /= norm
    SEqHatDot_4 /= norm
    
    # Compute the quaternion rate measured by the gyroscope
    SEqDot_omega_1 = -halfSEq_2 * w_x - halfSEq_3 * w_y - halfSEq_4 * w_z
    SEqDot_omega_2 = halfSEq_1 * w_x + halfSEq_3 * w_z - halfSEq_4 * w_y
    SEqDot_omega_3 = halfSEq_1 * w_y - halfSEq_2 * w_z + halfSEq_4 * w_x
    SEqDot_omega_4 = halfSEq_1 * w_z + halfSEq_2 * w_y - halfSEq_3 * w_x
    
    # Compute then integrate the estimated quaternion derivative
    SEq_1 += (SEqDot_omega_1 - (beta * SEqHatDot_1)) * deltat
    SEq_2 += (SEqDot_omega_2 - (beta * SEqHatDot_2)) * deltat
    SEq_3 += (SEqDot_omega_3 - (beta * SEqHatDot_3)) * deltat
    SEq_4 += (SEqDot_omega_4 - (beta * SEqHatDot_4)) * deltat
    
    # Normalize quaternion
    norm = sqrt(SEq_1 * SEq_1 + SEq_2 * SEq_2 + SEq_3 * SEq_3 + SEq_4 * SEq_4)
    SEq_1 /= norm
    SEq_2 /= norm
    SEq_3 /= norm
    SEq_4 /= norm
    
    return (SEq_1, SEq_2, SEq_3, SEq_4)

if __name__ == "__main__":
    SEq = (0.7071, 0.0, 0.7071, 0.0)
    Eg = (0.0, 0.0, 0.0, 1.0)
    Sa = (0.0, 0.3333, 0.3333, 0.3333)
    
    # Show that f_g_1 and f_g_2 are in fact equivalent
    f1 = f_g_1(SEq, Eg, Sa)
    f2 = f_g_2(SEq, Sa)
    
    print("Check for equality")
    print("Obj Func Quat:", f1, sep=" ")
    print("Obj Func Matrix:", f2, sep=" ")
    print()
    
    # Show that d_f_1 and d_f_2 are in fact equivalent
    J = J_g(SEq)
    
    print("Check for equality")
    print("Note: The results will not be normalized")
    print("Descent grad 1:", d_f_1(J, f1), sep=" ")
    print("Descent grad 2:", d_f_2(J, f2), sep=" ")
    print()
    
    # Show that the update functions are equivalent in their results
    print("Check for equality")
    
    #print("My update:", , sep=" ")
    
    print("Their update:", update_2(0.72, 0.3, 0.02, 2.0, 0.3, 7.1), sep=" ")
    print()
