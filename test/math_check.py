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
