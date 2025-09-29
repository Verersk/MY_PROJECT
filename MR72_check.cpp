static void check_MR72() {

    float X = obj_info.getDistX();
    float Y = obj_info.getDistY();

    float dist_vector = sqrtf(powf(X, 2) + powf(Y, 2));
    float yaw = degrees(atanf(X / Y)) - 45.0;

    if (yaw < 0) {
        yaw += 360.0;
    }

    printf("DistX = %.2f  DistY = %.2f  Vector = %.2f, Angle = %.2f \n\r", obj_info.getDistX(), obj_info.getDistY(), dist_vector, yaw);

    obj_info.pop_DistX();
    obj_info.pop_DistY();
}
