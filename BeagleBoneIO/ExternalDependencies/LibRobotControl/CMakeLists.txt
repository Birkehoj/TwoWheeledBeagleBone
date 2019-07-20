cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project("LibRobotControl" LANGUAGES C)

set(libRobotControlPath "LibRobotControl/library")

add_library(robotics_cape
  STATIC
    ${libRobotControlPath}/src/button.c
    ${libRobotControlPath}/src/cpu.c
    ${libRobotControlPath}/src/dsm.c
    ${libRobotControlPath}/src/led.c
    ${libRobotControlPath}/src/mavlink_udp.c
    ${libRobotControlPath}/src/model.c
    ${libRobotControlPath}/src/motor.c
    ${libRobotControlPath}/src/pinmux.c
    ${libRobotControlPath}/src/pthread.c
    ${libRobotControlPath}/src/start_stop.c
    ${libRobotControlPath}/src/time.c
    ${libRobotControlPath}/src/version.c
    ${libRobotControlPath}/src/bmp/bmp.c
    ${libRobotControlPath}/src/io/adc.c
    ${libRobotControlPath}/src/io/encoder_eqep.c
    ${libRobotControlPath}/src/io/gpio.c
    ${libRobotControlPath}/src/io/i2c.c
    ${libRobotControlPath}/src/io/pwm.c
    ${libRobotControlPath}/src/io/spi.c
    ${libRobotControlPath}/src/io/uart.c
    ${libRobotControlPath}/src/math/algebra.c
    ${libRobotControlPath}/src/math/algebra_common.c
    ${libRobotControlPath}/src/math/filter.c
    ${libRobotControlPath}/src/math/matrix.c
    ${libRobotControlPath}/src/math/other.c
    ${libRobotControlPath}/src/math/polynomial.c
    ${libRobotControlPath}/src/math/quaternion.c
    ${libRobotControlPath}/src/math/ring_buffer.c
    ${libRobotControlPath}/src/math/vector.c
    ${libRobotControlPath}/src/mpu/mpu.c
    ${libRobotControlPath}/src/pru/encoder_pru.c
    ${libRobotControlPath}/src/pru/pru.c
    ${libRobotControlPath}/src/pru/servo.c
  )

target_include_directories(robotics_cape SYSTEM
  PUBLIC
    ${libRobotControlPath}/include
)
