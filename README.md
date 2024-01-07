this is a simple ic sercer build with c++ languge 
 
first lets define server and what is server


-------------server-------------

componment :
    - Client:
        we will get all client info saved and if some one banned his ip will be saved
        a client can connect to server and get welcome board 
        tow client can connect to each other and chat privertly via server this will need to crate somthing like chaneel but it have only the consorned Users
    - Channels:
        for chanelle we will create an ordred map that collect every alive client and if a msg came to chanlle we will broadcast it to all client
        if user is banned from channel they can't joing it with thier nick and ip
    - Commands:
        all commands to interact with server will try to implement them as object that take user and thier parameters
