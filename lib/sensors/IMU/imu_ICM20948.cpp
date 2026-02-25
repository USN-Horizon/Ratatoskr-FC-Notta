#include "imu_ICM20948.h"

IMU_ICM20948::IMU_ICM20948(TwoWire& wire, int i2c_addr, const String& name)
    :
    Sensor(name)
{
    if(!imu.init()){
        return;
    }

    imu.autoOffsets();

   /* You can set the following modes for the magnetometer:
   * AK09916_PWR_DOWN          Power down to save energy
   * AK09916_TRIGGER_MODE      Measurements on request, a measurement is triggered by
   *                           calling setMagOpMode(AK09916_TRIGGER_MODE)
   * AK09916_CONT_MODE_10HZ    Continuous measurements, 10 Hz rate
   * AK09916_CONT_MODE_20HZ    Continuous measurements, 20 Hz rate
   * AK09916_CONT_MODE_50HZ    Continuous measurements, 50 Hz rate
   * AK09916_CONT_MODE_100HZ   Continuous measurements, 100 Hz rate (default)
   */
    imu.setMagOpMode(AK09916_CONT_MODE_20HZ);

    /* ICM20948_ACC_RANGE_2G      2 g   (default)
    *  ICM20948_ACC_RANGE_4G      4 g
    *  ICM20948_ACC_RANGE_8G      8 g
    *  ICM20948_ACC_RANGE_16G    16 g
    */
    imu.setAccRange(ICM20948_ACC_RANGE_16G);
    /*  ICM20948_GYRO_RANGE_250       250 degrees per second (default)
   *  ICM20948_GYRO_RANGE_500       500 degrees per second
   *  ICM20948_GYRO_RANGE_1000     1000 degrees per second
   *  ICM20948_GYRO_RANGE_2000     2000 degrees per second
   */
    imu.setGyrRange(ICM20948_GYRO_RANGE_250);

    /*  Choose a level for the Digital Low Pass Filter or switch it off.
   *  ICM20948_DLPF_0, ICM20948_DLPF_2, ...... ICM20948_DLPF_7, ICM20948_DLPF_OFF
   *
   *  IMPORTANT: This needs to be ICM20948_DLPF_7 if DLPF is used in cycle mode!
   *
   *  DLPF       3dB Bandwidth [Hz]      Output Rate [Hz]
   *    0              246.0               1125/(1+ASRD) (default)
   *    1              246.0               1125/(1+ASRD)
   *    2              111.4               1125/(1+ASRD)
   *    3               50.4               1125/(1+ASRD)
   *    4               23.9               1125/(1+ASRD)
   *    5               11.5               1125/(1+ASRD)
   *    6                5.7               1125/(1+ASRD)
   *    7              473.0               1125/(1+ASRD)
   *    OFF           1209.0               4500
   *
   *    ASRD = Accelerometer Sample Rate Divider (0...4095)
   *    You achieve lowest noise using level 6
   */
    imu.setAccDLPF(ICM20948_DLPF_6);
    /*  Choose a level for the Digital Low Pass Filter or switch it off.
   *  ICM20948_DLPF_0, ICM20948_DLPF_2, ...... ICM20948_DLPF_7, ICM20948_DLPF_OFF
   *
   *  DLPF       3dB Bandwidth [Hz]      Output Rate [Hz]
   *    0              196.6               1125/(1+GSRD)
   *    1              151.8               1125/(1+GSRD)
   *    2              119.5               1125/(1+GSRD)
   *    3               51.2               1125/(1+GSRD)
   *    4               23.9               1125/(1+GSRD)
   *    5               11.6               1125/(1+GSRD)
   *    6                5.7               1125/(1+GSRD)
   *    7              361.4               1125/(1+GSRD)
   *    OFF          12106.0               9000
   *
   *    GSRD = Gyroscope Sample Rate Divider (0...255)
   *    You achieve lowest noise using level 6
   */
    imu.setGyrDLPF(ICM20948_DLPF_6);

    /*  Acceleration sample rate divider divides the output rate of the accelerometer.
   *  Sample rate = Basic sample rate / (1 + divider)
   *  It can only be applied if the corresponding DLPF is not off!
   *  Divider is a number 0...4095 (different range compared to gyroscope)
   *  If sample rates are set for the accelerometer and the gyroscope, the gyroscope
   *  sample rate has priority.
   */
    imu.setAccSampleRateDivider(10);
    /*  Gyroscope sample rate divider divides the output rate of the gyroscope.
   *  Sample rate = Basic sample rate / (1 + divider)
   *  It can only be applied if the corresponding DLPF is not OFF!
   *  Divider is a number 0...255
   *  If sample rates are set for the accelerometer and the gyroscope, the gyroscope
   *  sample rate has priority.
   */
    //imu.setGyrSampleRateDivider(10);

    good = true;
}

IMU_ICM20948::~IMU_ICM20948() = default;

void IMU_ICM20948::Read(FC_Data &data) {
    imu.readSensor();

    xyzFloat accValues, gyroValues, magValues;
    imu.getAccRawValues(&accValues);
    imu.getGyrRawValues(&gyroValues);
    imu.getMagValues(&magValues);

    data.imu_acc_raw = {accValues.x, accValues.y, accValues.z };
    data.imu_ang_vel_raw = {gyroValues.x, gyroValues.y, gyroValues.z };
    data.imu_mag_raw = {magValues.x, magValues.y, magValues.z };
}