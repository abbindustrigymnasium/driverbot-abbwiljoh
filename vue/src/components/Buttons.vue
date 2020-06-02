<template>
  <v-container id="box">
   <span id="hide"> {{Disconnect}}</span>
    <v-card class="elevation-12" color="grey lighten-1">
      <v-layout row>
        <v-flex class="justify-center mb-6">
          <v-btn class="ma-2" v-if="connected" tile color="red" icon @click="speed=850"> <!-- hastighetsknapp -->
            85
            <v-icon>directions_car</v-icon>
          </v-btn>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','f'+speed); SubscribeLog('directionlog');" 
          > <!-- ^^^ Varje framåt/bakåt/vänster/höger-knappar kallar samma funktioner: För att skicka MQTT-meddelande och för att få svar från bilen. -->
            <v-icon>keyboard_arrow_up</v-icon>
          </v-btn>

          <v-btn class="ma-2" tile v-if="connected" color="blue" icon @click="speed=900">
            90
            <v-icon>directions_car</v-icon>
          </v-btn>
        </v-flex>
      </v-layout>
      <v-layout row>
        <v-flex md6>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','l90'); SubscribeLog('directionlog');"
          >
            <v-icon>keyboard_arrow_left</v-icon>
          </v-btn>
        </v-flex>

        <v-flex md6>
          <v-btn v-if="!connected" class="ma-2" tile large :color="car" icon @click="Connect()">
            <v-icon>directions_car</v-icon>
          </v-btn>
          <v-btn v-else class="ma-2" tile large :color="car" icon @click="Send('direction','f0'); SubscribeLog('directionlog');">
            <v-icon>pause</v-icon>
          </v-btn>
        </v-flex>
        <v-flex md6>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','r90'); SubscribeLog('directionlog');"
          >
            <v-icon>keyboard_arrow_right</v-icon>
          </v-btn>
        </v-flex>
      </v-layout>
      <v-layout row>
        <v-flex class="justify-center mb-6">
          <v-btn class="ma-2" v-if="connected" tile color="green" icon @click="speed=950">
            95
            <v-icon>directions_car</v-icon>
          </v-btn>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','b'+speed); SubscribeLog('directionlog');"
          >
            <v-icon>keyboard_arrow_down</v-icon>
          </v-btn>

          <v-btn class="ma-2" tile v-if="connected" color="purple" icon @click="speed=1000">
            99
            <v-icon>directions_car</v-icon>
          </v-btn>
        </v-flex>
      </v-layout>
    </v-card>
  </v-container>
</template>

<script>
//Bibliotek som ska användas
var mqtt = require("mqtt");
export default {
  name: "Buttons",
  props: {
    //Data som skickas in i komponenten
  },
  data() {
    //All data som ska finnas i komponenten
    return {
      connected: false,
      car: "green",
      clientId: "notyetAssigned",
      client: null,
      speed: 850,
      ticklabels: ["Långsamt", "Snabbare", "Snabbast"],
      options: {}
    };
  },
  computed: {
    Disconnect() {    //Här är en funktion som kallas från html-delen, som i sin tur kallar en funktion i store.js
      if (this.$store.getters.connected == false) {
        return true;
      }
      return false;
    }
  },
  watch: {
    //Om du vill logga någonting när det förändras i htmldelen. se exempel nedan
    Disconnect: {
      handler: function(newVal) {
        if (newVal == true) {
          this.connected = false;
          this.client = mqtt.disconnect;
          this.car = "green";
        }
      }
    }
  },
  methods: {
    //Metoder
    Connect() {
      //https://github.com/mqttjs/MQTT.js/blob/master/README.md
      var ref = this;
      if (this.connected == true) {
        return "";
      }
      let User = this.$store.getters.GetUser;
      this.clientId =
        "WilliamBilKontroll" +      //ClientID måste vara unikt så några siffror randomiseras för ID:t
        Math.random()
          .toString(16)
          .substr(2, 8);
      var mqtt_url = User.adress;
      var url = "mqtt://" + mqtt_url;     //Lite fler credentials för ansluta till MQTT
      var options = {
        port: User.port,
        clientId: this.clientId,
        username: User.name,
        password: User.password
      };
      this.options = options;
      // console.log("connecting");
      this.client = mqtt.connect(url, options);
      // console.log("connected?");

      this.client
        .on("connect", function() {
          // console.log("success");
          ref.Connecting(true);
        })
        .on("error", function() {
          // console.log("error");
          ref.Connecting(false);
        })
        .on("close", function() {     //Så man inte är connectad om anslutningen bryts.
          ref.Connecting(false);
          // console.log("closing");
        });
    },

    Connecting(connected) {
      this.connected = connected;
      this.$store.dispatch("Connect", connected);
      // console.log(this.connected)
      if (connected == false) {
        this.car = "red";             //Om bilen inte anslutits blir bilikonen röd
      } else {
        this.car = "blue";
        this.Send("direction", this.clientId + " har anslutits.");
      }
    },

    Send(adress, message) {     //Publicerar till MQTT
      // console.log(message);
      this.client.publish(
        this.options.username + "/" + adress,
        message
      );

      // this.$store.dispatch("addToLogger", message);
    },
    SubscribeLog(adress) {    //Mitt viktigaste tillägg till hemsidan:
      this.client.subscribe(this.options.username+'/'+adress, {qos: 1}) //Funktion för att läsa av och lägga till MQTT-meddelanden från bilen
      this.client.on('message', (topic, message)=> {                   //och lägger till meddelandet i loggern.
        this.$store.dispatch("addToLogger", message)
      })
      }
  }
};
</script>

<!-- CSS -->
<style scoped>
.big {
  font-size: 25px;
}
#Cooltext {
  color: black;
  text-decoration: underline;
}
#box {
  width: 400px;
  height: 400px;
}
#hide{
 display: none;
}
#logger {
  position: fixed;
  bottom: 0;
  right: 0;
  width: 300px;
  height: 300px;
  border: black dotted 2px;

  word-wrap: break-word;
}
</style>
