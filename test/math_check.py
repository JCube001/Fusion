#!/usr/bin/env python3
#
# This script helps to verify that this library's math is equivalent to the math
# in the AHRS article by Sebastian O.H. Madgwick.
#
# Note: All tuples must be normalized.
#

# Quaternion cross product
def q_cross(a, b):
    return (a[0]*b[0] - a[1]*b[1] - a[2]*b[2] - a[3]*b[3],
            a[0]*b[1] + a[1]*b[0] + a[2]*b[3] - a[3]*b[2],
            a[0]*b[2] - a[1]*b[3] + a[2]*b[0] + a[3]*b[1],
            a[0]*b[3] + a[1]*b[2] - a[2]*b[1] + a[3]*b[0])

# Accelerometer objective function (our quaternion version)
def f_g_1(SEq, Eg, Sa):
    SEqq = (SEq[0], -SEq[1], -SEq[2], -SEq[3])
    q_tmp = q_cross(q_cross(SEqq, Eg), SEq)
    
    return (q_tmp[0] - Sa[0], q_tmp[1] - Sa[1],
            q_tmp[2] - Sa[2], q_tmp[3] - Sa[3])

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
    pass

if __name__ == "__main__":
    # Show that f_g_1 and f_g_2 are in fact equivalent
    SEq = (0.7071, 0.0, 0.7071, 0.0)
    Eg = (0.0, 0.0, 0.0, 1.0)
    Sa = (0.0, 0.3333, 0.3333, 0.3333)
    
    print("Check for equality")
    print("Note: Ignore the real component of the quaternion")
    print("Obj Func Quat:", f_g_1(SEq, Eg, Sa), sep=" ")
    print("Obj Func Matrix:", f_g_2(SEq, Sa), sep=" ")
    print()
    
    # Show that J_g_f_g_1 and J_g_f_g_2 are in fact equivalent
    # TODO
