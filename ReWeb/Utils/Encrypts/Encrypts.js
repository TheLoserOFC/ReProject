const crypto = require('crypto');
const ReplaceAll = require('string.prototype.replaceall')
const ENC_KEY = "12345678909876543212345678909876"; //32 Bytes
const IV = "1234567890987654"; //16 Bytes

function setCharAt(str,index,chr) {
  if(index > str.length-1) return str;
  console.log(str);
  return str.substring(0,index) + chr + str.substring(index+1);
}

class Encrypts {
  AESencrypt(text) {

    let cipher = crypto.createCipheriv('aes-256-cbc', ENC_KEY, IV);
    let encrypted = cipher.update(text, 'utf8', 'base64');
    return (encrypted += cipher.final('base64'));
  };

  AESdecrypt(text) {
    let decipher = crypto.createDecipheriv('aes-256-cbc', ENC_KEY, IV);
    let decrypted = decipher.update(text, 'base64', 'utf8');
    return (decrypted += decipher.final('utf8'));
  };

  GZencrypt(text, lista_new) {
    const alfabeto = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9"," "];
    const alfabeto2 = ["Z","Y","X","W","V","U","T","S","R","Q","P","O","N","M","L","K","J","I","H","G","F","E","D","C","B","A","z","y","x","w","v","u","t","s","r","q","p","o","n","m","l","k","j","i","h","g","f","e","d","c","b","a","0","9","8","7","5","6","4","3","2","1","_"];
   //var _new = lista_new;
    var newtext = "pqp em porra";
    //var newtext = "pqp em porra";
    var arraystr = ["a", "c", "b"];

    
    
    return "a";
  }

  
}



module.exports = new Encrypts();

