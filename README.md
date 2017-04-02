# [TTK4155 - Embedded and Industrial Computer Systems Design](http://www.ntnu.edu/studies/courses/TTK4155)

**Course content:** Design of embedded computer systems. Computer architectures and system components for embedded and industrial applications. Microcontrollers and specialized microprocessors. Parallel and serial bus systems. Datacommunication in industrial environments. Analog/digital interfaces.

**Project:** In this course, we had a large term project where we created a computer controller electromechanical ping pong game. The main challenge was to assemble the hardware components and develop the software for the microcontrollers, making a fully functional embedded computer system that enabled us to play a refreshing game of ping pong! The project was divided into nine parts, that we did more-or-less on a week-to-week basis: 

  - **Part 1** - Initial assembly of microcontroller and RS-232
  - **Part 2** - Address decoding and external RAM
  - **Part 3** - A/D converting and joystick input
  - **Part 4** - OLED display and user interface
  - **Part 5** - SPI and CAN controller
  - **Part 6** - CAN-bus and communication between nodes
  - **Part 7** - Controlling servo and IR
  - **Part 8** - Controlling motor and solenoid
  - **Part 9** - Completion of the project and extras

**Part 1** - **part 5** were done on `node 1`, which consisted of our "main board", with **Atmega162**, and the USB multifunction card.

![node 1](https://lh3.googleusercontent.com/BsFxsVxMSpB2jZan9GU55XqtgzFUxJfBUBSd4L1ZHMvviyncFf9cCo8vc7DxqjjvIrRBnLJqdtTNb9yXxTCcoMDmXXjewMRQCCEoEnCu8b8aW3BNayCi0qWKmQgRkdMywmmu6nZh01M3iIi5sc6KQSO6Jb3u9fiRMjDUhZsXqkfbZKPIWnlb57Kg-S01O64NXfTlXDTP10qeMNa5_PgTdZyrc6TFJC3SofCzvvcQKRg0QZOra781vSTlFv7npYOfpiEeyzis3Na8KfrCcbvNKQQPBb7St1ZmG5a3cUPENhd6vlo2g4daGSPuVV2XOJXpFzEziHWSRPNnPlw4hRK-iB4ebR-tp9EhFX3DCTGXyw_r6G_IHzLXcdXRj79BSoh4KoCYzsEZDqMUzXzODoyjjUGCuLDMl-LKG6FIfNuYn38cCq3J_ENmDZL4ViP-SnNYqPzNyf2HVMwnjAll_ePRe1RosUp23kHTmSF7lNwfZgDP4racAGncIMoOAPcJjB2wVCRI6odHV71NLhLdyeLkPB9nqbnxU4rESpw4Ho_VM92SRLPG7wnfLSFDaFHVrjEIX-LIdPG5cmbBOy-g2wG6nZ5Q6UqUhCykmxDCMW1r1ET41l4qykINHpsjDkB-Gesn-BDOlveYoOAVTUJ08DFepGLQUkRklrUbO5yLmr9jzoQ=w1449-h966-no)

And here's a more detailed view of the board in `node 1` itself

![node 1 without USB multifunction card](https://lh3.googleusercontent.com/pdi_NbMJBftXRLt6jPqJf8rYEZZW_sCvBvnrEsAYBup7uFI3CrwDNxf4MGydlf9Knc1dOCE9IGj7cXfzVzvZVqB6K8dAgJZzKmKnAnjNWxH5yPaSSX4IjbF8zeGNu-S4VV3JvjDF6nt6M-leq6hRSECMakQams1dz073eqkyYO2j9bsiL0lNbDxbpx5qHE1mJO-N-Y-69tZVL1NF5MGf9qq329LsKSFZ6d-mbQQj4fQY_U6vaFQvJOOoiobWazQTrKRDoWxu1Cq7jbk1hHXmVnlCyiy7igQQHPm2UDsQyEkWzgd-vaQkYPEuxlY8bLadHo7yeXZNnQb0PWAQxmB4Edop7eHSQcNTExHAkpJslzj_yykdTplCMKpYNYZYelq2wla0kxNFWIjpTDc1-i2lLwY1rQ92BLJx6uclbEQyYarAbrXvnDfEcmc-RTCIQPQRme7Ogb74Jy_sfVeHUSIF9D_WbjIMA8LW8WktTx4wE_vP_pFZG-QXUb845z7XPtiSF3QheGqNSuAeEYDwNkqBCZcOVD_h50lIiLXPC21gm1lSE9gjKrlvc5pzyrc_B3vNJvhxm5syw71nYw1MOddPUlAFLcOeEZFt9-6P1Itq4SjM6z3IAX1iZ0kYH8FNCnU2Qk6qM0tDW-OfRnbLHjdgAf_5j1mBYvYu_f_vFwYTSWI=w1177-h966-no)

**Part 6** - **part 8** were mostly done on `node 2`, which consisted of a PCB with several useful components, and an **Arduino Mega 2560 (Atmega2560)**

![node 2](https://lh3.googleusercontent.com/1lP1FKvvnAPZLNjzyrmI8Z8nI6kiNmtbNBiJxCGswDtK8s__cghyWD9tNA82Vy9p4Cqm6Uz7w1vizwKphPdETuFQyjMSNytHyxTEnO3tpZ1k0aiP1dKzdof2JVLamjoVPC5cX6JrX1gLbfSGxa8HxrQMog6YxXhFwNsq_LdBS_QyDAt3v5NpVMLYS2EOAhVeDJjdduGH7VylRrl0RUZCdJzcVTXhsdy4Tt-uIf8zFaDJWn9wakcbUXKeKLittrVS-gcPMel5svMMRQ7vwfA9bF4ej4089tVXhCSG6pmNDDqWMeEtON2wvhHaPOzrMz4KmFTKzCD85ShAeuQdUOqL_mELIZ19eaY9rdnd-lN2NJwpU7_gtOeIOrkHp71OPlreoPV6pOn_sf3TgeA8rS6dvs9mnFfrTsP2UwIYD2FWoSo2ZmLgYvmk4mQuIcseQuBbzEor437FuOUiLV_O3-x7Gcw880Q_qlEuO-hnyDKKNDwR7vuYVne2wO4eZBld9HTEZ1h0lP5dBKC6qJLfLtpYLbIoZ1oPQm5_CMu8BCQkefho6e5692yRtmcdNq22n8ncMgW0yXXPU65hUAWdAjJgmlwNT1sGnfPKhVXGl58ViOQlg2V9GNGXk6FMQYf4BdFXzHFQsQvV8KY22Z3bE7o08AtNHkW8Hd1tpi2IDb7fbXs=w1449-h966-no)

We also needed a relay circuit for the solenoid on the ping pong board, and a filter for the IR-sensors.

![circuits for IR-filter and solenoid relay](https://lh3.googleusercontent.com/DqHa0NZ3p44sFIFo29yepGgH8bbm49HnclIaXezamAIWErJ1_lNLu3ixnC8_MShnxwOf0SppHwWJxM8koEq65dLChCyVnBFw1qAxhcF1yJy0NKPAnDFOsOcGoZAoCrHjSMvgGmFFyYmrzN0T73e33Mh-27Kr9q2GWgQiGMjthrCfZY8c9ffcEBeedPMlaU7rHddbWOa6qKXRpk8XLTLj7CzSqSEna5LoFs5DVgRCuVdHbWRbaxSQj3WuAeAZQmriyNNu-W3__QHcWTJg_phCAZg_QD-dJZc5wE_d9vTnrwBENGMJ-bv1wOseqCoiwHBYeRitxeiFC5L0xXj-E_9urDQTAIybG8FpESddT7cPgzyWE9H7LnR7z7kRoFnREAvy3FxmGKlYUX-gbm4YgEZ0F2K7tXgZv-T2IC61zCrmVYj9n0ae0rgOeVCtH6196F0SgGfQt49VV0SFanQB0M6BwZyM_yhOfzfI4lcncnrfLYn9sPQb1GoqdK8DpPNzFTVwoXv26WxfGj5Hv-uR7WRd_8cFsvzD2TqAFe8sYiNX4McikmE3FPaZkL1aCRDEfjcrB0bklScbqTal_aU0HhDc78zbINulBOLJCBJuk2672U7w2hbrjGPR7goKZ_QM0ZN5C365t2-hCUzWX4a5rZXqZoek6WpSjpZtQeUpm11dCZM=w1449-h966-no)

**Part 9** is where we finalized the project. This meant completing `node 1` and `node 2` as well as their interaction. Also, we added `node 3`, which consisted of a Genuino UNO. The node was used to play wonderful music with a piezo buzzer.

![node 3](https://lh3.googleusercontent.com/To_5VMaNnvcLWfMme87oS0xxTVeDff7miAAmek-GpjECYJWqGj7PYU2nzKqOuIa3bh8aa3BMoPVprWhCtuS-IU7gQ9aaOJ_ThJBtdktYRGEiQEGlUPimkHFqBQs6lXEt50hrDJPYMBTgl_rCyCIH3ZZQvT_JXgh11HsqEaPezzPAfDH_BF49Ri1MkfCDbrq8af5CSp8BsaA_fqVLJiZUC0G1Rmkk-wwh0FqtGOU0pFIAFAXO9p3CV3RC4fwoIzJoVT8yN6vzJoa4HkZodRsNldio6544Y30orp4Nf9S3RpZuYJIxzub1kV41fiv72NIs7WnCWt-IixZ1FB8E1AvWKRsc8hZHknwy2RVwGUJeww5PmBi2fNYTqmJaOCcbzm9HsV2DRkElKcd1Q1qQAoEkfhQ3TvuFmimuPbfDONkrRF_nXitHAksxbDcyd-cSJw33XpYTOknIOAdM40exQVuLYspg85D-Rvh1v_N31cK9IMhwRx46xdzqNchRJYj9PBTQSFVUbw9Zf3AfqqgPAl5x9s0wbsUBBqcW0XQTvx7JDkcv5egwdBnASYPpj-YF6cG-W600kOMQO2UCCChy52SociIiwwXEMOiQnwmSy_aWks7QpydQLyyA1iqxb-wyrlLprnCLMqvFWpVLPB4syOf2HK9J4JAwdveqx_4OLO_ia5s=w1449-h966-no)

**Part 9** is where we were able to add creative ideas to the project and additional features. Here are the features we added to the project: 

  - **Varying difficulty:** Different tuning of _PID_-controller (position).
  - **Creative use of display:** Scrolling text horizontally, adaptive menu and other advanced features. 
  - **Sound:** `Game over` sound, several music tunes, playable during game play, adjustable volume (potentiometer).
  - **EEPROM:** Used to save high scores in-between gaming sessions.

Finally, a very short demo of the system (in Norwegian). This was shot minutes after the presentation, right before we had to disassemble the whole system. The video is therefore quite rushed, so don't expect too much quality-wise. 

_Press the picture below to play the video_ (**opens in a new tab**)

[![Video demo of term project](https://lh5.googleusercontent.com/zP3AIb-MDHumwE9sQZIoNg0bkWC8aHkg8k06-uPZKN78wgf5pz6YeB8cBHj4PVABIxvj_tiNQbAPiSk=w640-h360-n-k-rw)](https://drive.google.com/file/d/0B3gcOnjFGnOzVkZMNlVDQ3Bwakk/view)
