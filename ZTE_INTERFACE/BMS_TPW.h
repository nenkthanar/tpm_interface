 
 #define SEND_HEADER 0xBA
 #define OPERATION_OK 0x00
 #define NO_TAG 0x01
 #define READ_FAIL 0x04
 #define WRITE_FAIL 0x05
 #define LOGIN_SUCCEED 0x02
 #define LOGIN_FAIL 0x03

 byte HEADER,LEN,CMD,STATUS,UID[8],TYPE,CHKSUM,BOX,AFI,DSFID;
  byte rx_buff[54];

  byte checksum(byte (*values),int length){
  byte result = values[0];
  for (int i = 1; i < length; i++)
  result ^= values[i];
  return result;
  }

//   0x7E; //head buf[1]
//   = 0x01; //addr buf[2] = 0x01;
//   //CID buf[3] = 0x00; //data
//   length
//   BUF [4] = chk; / / check code
//   buf[5] = 0x0D; //tail
  int readBlock(int startblock,int number,byte storedata[9]){
        byte *frame;
        frame = (byte *) malloc(5 * sizeof(byte));
        frame[0] = 0; //head
        frame[1] = 3;
        frame[2] = 0x03;
        frame[3] = 0x04;
        frame[4] = checksum(frame, 4); 
        
        Serial1.write(frame, 5);
        free(frame);
        frame = NULL;
        while (1){    
           while (Serial1.available()==0); 
           if(Serial1.read() == 0xBD) break;
            }     
           while (Serial1.available()==0);    
           LEN = Serial1.read();
           while (Serial1.available()==0);   
           CMD = Serial1.read();
           while (Serial1.available()==0) ;   
           STATUS = Serial1.read();
           if (STATUS == 0x00) { // Select Success
           for (int i = 0; i < int(LEN) - 3; i++) {      
           while (Serial1.available() == 0) ;
           byte c = Serial1.read();
              storedata[i] = c;
           }  
           }
          
        while (Serial1.available() == 0) ;    
        CHKSUM = Serial1.read();
        if (STATUS == 0x00){ // operation ok
            Serial1.flush();
            return 0;
            }
            else{
            return 1;
           }
          }


  void BMS_Read(){
  if(Serial1.available()){
    
  }
  }

