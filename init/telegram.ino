void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    
    if (text == "/307") {
//      bot.sendChatAction(chat_id, "typing");
//      delay(2000);
      bot.sendMessage(chat_id, "T: " + temp + "\nH: " + hum);
    }

    if (text == "/muzlo") {
      bot.sendMessage(chat_id, "Эта хуйня больше не прокатит))))");
    }

    if (text.substring(0, 9)  == "/setalarm") {       
      if (text.substring(10, 12) != "" && text.substring(13, 15) != "") {
        alarm = true;

        ah = text.substring(10, 12).toInt();
        am = text.substring(13, 15).toInt();

        if (ah > 0 && ah < 24 && am > 0 && am < 60) {
//        bot.sendChatAction(chat_id, "typing");
//        delay(2000);
        bot.sendMessage(chat_id, "Alarm set on " + String(ah) + ":" + String(am));
        } else {
//          bot.sendChatAction(chat_id, "typing");
//         delay(2000);
         bot.sendMessage(chat_id, "Request must look like '/setalarm HH:MM'");
        }
      }
    }

    if (text == "/alarm off") {
        bot.sendMessage(chat_id, "Alarm off");
        alarm = false;
      }
  
      if (text == "/alarm status") {
        if (alarm) {
  //        bot.sendChatAction(chat_id, "typing");
  //        delay(2000);
          bot.sendMessage(chat_id, "Alarm was set on " + String(ah) + ":" + String(am));
        } else {
  //        bot.sendChatAction(chat_id, "typing");
  //        delay(2000);
          bot.sendMessage(chat_id, "No alarm was set up");
        }
      }
  }
}
