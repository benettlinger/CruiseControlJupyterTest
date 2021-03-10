//
// Created by localuser on 3/10/2021.
//

#ifndef C_VERSION_CAN_FUNCTIONS_H
#define C_VERSION_CAN_FUNCTIONS_H

#endif //C_VERSION_CAN_FUNCTIONS_H

void can_send_cmd(const char *channel, const char *string_id, const char *string_data){
    int idx_delimiter;  // Position of the delimiter between id and data
    // Determine delimiter position
    uint8_t id_length = strlen(string_id);
    if (id_length==3){
        printf("Regular CAN ID\n");
        idx_delimiter = 3;
    }
    else if (id_length==8){
        printf("Extended CAN Frame\n");
        idx_delimiter = 8;
    }
    else{
        printf("Invalid CAN ID of length: %i", id_length);
        return;
    }
    // Create cansend message
    char message[30];
    format_message(string_id, string_data, idx_delimiter, message);
    printf("Sending %s on channel %s\n", message, channel);
    // Format command
    char command[100];
    sprintf(command, "cansend %s %s >/dev/null 2>&1", channel, message);
    system(command);
}

int can_receive(const char *channel, char *id,  char *dlc, char *data){

    // Input: Channel
    // Output: message ID, DLC, data
    int s, i;
    int nbytes;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    // Open the socket
    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return 1;
    }

    strcpy(ifr.ifr_name, channel);  // channel was originally "vcan0"
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;


    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        return 1;
    }


    nbytes = read(s, &frame, sizeof(struct can_frame));


    if (nbytes < 0) {
        perror("Read");
        return 1;
    }

    sprintf(id,"%03X", frame.can_id);

    if (strlen(id)==8){
        if (id[0]=='9'){
            id[0]='1';
        }
        else if (id[0]== '8'){
            id[0]='0';
        }
    }

    sprintf(dlc,"%d", frame.can_dlc);
    bytes2hexstring(frame.data, data, 8);

    if (close(s) < 0) {
        perror("Close");
        return 1;
    }

    return 0;
}