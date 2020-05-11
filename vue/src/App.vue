<template>
  <v-app id="content">
    <v-toolbar app id="toolbar">
      <v-toolbar-title class="headline text-uppercase">
        <span>Robot</span>
        <span class="font-weight-light">Car</span>
      </v-toolbar-title>

      <v-spacer></v-spacer>
      <v-btn color="primary" dark @click.stop="dialog = true">Anslutningsalternativ</v-btn>
      <v-btn target="_blank" @click="Switch=!Switch">
        <span v-if="Switch!==true" class="mr-2">Buttons 1</span>
        <span v-else class="mr-2">Buttons 2</span>
      </v-btn>
    </v-toolbar>

    <v-content>
      <v-row align="center" justify="center">
        <v-dialog v-model="dialog" max-width="290" height="290">
          <v-card>
            <v-card-title class="headline">Anslutning till Server</v-card-title>

            <v-card-text style="height: 300px;">
              <v-text-field v-model="name" label="Name" filled></v-text-field>

              <v-text-field v-model="password" label="MQTT Password" filled></v-text-field>

              <v-text-field v-model="port" label="Port" filled></v-text-field>
              <v-text-field v-model="adress" label="Adress" filled></v-text-field>
            </v-card-text>

            <v-card-actions>
              <v-spacer></v-spacer>

              <v-btn color="green darken-1" text @click="save()">Spara</v-btn>
            </v-card-actions>
          </v-card>
        </v-dialog>

        <div>
          <Logger />

          <Buttons v-if="Switch" />
          <Buttons2 v-else />
        </div>
      </v-row>
    </v-content>
  </v-app>
</template>

<script>
import Buttons2 from "./components/Buttonsv2";
import Buttons from "./components/Buttons";
import Logger from "./components/Logger";

export default {
  name: "App",
  components: {
    Buttons,
    Buttons2,
    Logger
  },
  data() {
    return {
      Switch: false,
      dialog: false,
      name: "",
      password: "",
      port: "",
      adress: ""
    };
  },
  created() {
    let User = this.$store.getters.GetUser;
    this.name = User.name;
    this.password = User.password;
    this.port = User.port;
    this.adress = User.adress;
  },

  methods: {
    save() {
      let User = {
        name: this.name,
        password: this.password,
        port: this.port,
        adress: this.adress
      };

      this.$store.dispatch("Save", User);

      this.dialog = false;
    }
  },
  computed: {}
};
</script>
<style scoped>
.img {
  width: 40%;
  height: 40%;
  margin: auto;
  padding: 10px;
}
#logger {
  /* position: fixed;
  bottom: 0;
  right: 0; */
  width: 300px;
  height: 300px;
  border: black dotted 2px;

  word-wrap: break-word;
}

/* https://beautifuldingbats.com/pattern-generator/ https://css-tricks.com/using-svg/ */
#toolbar {
  background-image: url("data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTAwJSIgaGVpZ2h0PSIxMDAlIj48ZGVmcz48cGF0dGVybiBpZD0icGF0dGVybiIgd2lkdGg9IjUwIiBoZWlnaHQ9IjUwIiB2aWV3Qm94PSIwIDAgNDAgNDAiIHBhdHRlcm5Vbml0cz0idXNlclNwYWNlT25Vc2UiIHBhdHRlcm5UcmFuc2Zvcm09InJvdGF0ZSgxNDgpIj48cmVjdCBpZD0icGF0dGVybi1iYWNrZ3JvdW5kIiB4PSIwIiB5PSIwIiB3aWR0aD0iNDAwJSIgaGVpZ2h0PSI0MDAlIiBmaWxsPSIjNDk1MDU3Ii8+ICA8IS0tLS0+IDwhLS0tLT4gPHBhdGggZD0ibSAwIDAgaCA0MCIgc3Ryb2tlLXdpZHRoPSIxNCIgc3Ryb2tlPSIjNWM3Y2ZhIiBzaGFwZS1yZW5kZXJpbmc9ImF1dG8iIHN0cm9rZS1saW5lY2FwPSJidXR0IiBzdHJva2UtbGluZWpvaW49InJvdW5kIiBmaWxsPSJ0cmFuc3BhcmVudCIvPjxwYXRoIGQ9Im0gMCA0MCBoIDQwIiBzdHJva2Utd2lkdGg9IjE0IiBzdHJva2U9IiM1YzdjZmEiIHNoYXBlLXJlbmRlcmluZz0iYXV0byIgc3Ryb2tlLWxpbmVjYXA9ImJ1dHQiIHN0cm9rZS1saW5lam9pbj0icm91bmQiIGZpbGw9InRyYW5zcGFyZW50Ii8+ICAgIDwhLS0tLT4gPCEtLS0tPiAgPHBhdGggZD0ibTAsMTQgaDQwIiBzdHJva2Utd2lkdGg9IjE0IiBzdHJva2U9IiNkZWUyZTYiIHNoYXBlLXJlbmRlcmluZz0iYXV0byIgc3Ryb2tlLWxpbmVjYXA9ImJ1dHQiIHN0cm9rZS1saW5lam9pbj0icm91bmQiIGZpbGw9InRyYW5zcGFyZW50Ii8+ICA8L3BhdHRlcm4+PC9kZWZzPiA8cmVjdCBmaWxsPSJ1cmwoI3BhdHRlcm4pIiBoZWlnaHQ9IjEwMCUiIHdpZHRoPSIxMDAlIiB5PSIwIiB4PSIwIi8+PC9zdmc+");
}
#content {
  background-image: url("data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTAwJSIgaGVpZ2h0PSIxMDAlIj48ZGVmcz48cGF0dGVybiBpZD0icGF0dGVybiIgd2lkdGg9IjUwIiBoZWlnaHQ9IjUwIiB2aWV3Qm94PSIwIDAgNDAgNDAiIHBhdHRlcm5Vbml0cz0idXNlclNwYWNlT25Vc2UiIHBhdHRlcm5UcmFuc2Zvcm09InJvdGF0ZSgxMTEpIj48cmVjdCBpZD0icGF0dGVybi1iYWNrZ3JvdW5kIiB4PSIwIiB5PSIwIiB3aWR0aD0iNDAwJSIgaGVpZ2h0PSI0MDAlIiBmaWxsPSIjNDk1MDU3Ii8+ICA8IS0tLS0+IDwhLS0tLT4gICAgPHBhdGggZD0iTTAsNDAgdi00MCBoNDAgTDI2IDcgaC0xMiB2MjYgeiIgZmlsbD0iIzg2OGU5NiIgc2hhcGUtcmVuZGVyaW5nPSJhdXRvIiBzdHJva2Utd2lkdGg9IjAiIHN0cm9rZT0iIzg2OGU5NiIgc3Ryb2tlLWxpbmVqb2luPSJyb3VuZCIvPiA8IS0tLS0+IDwhLS0tLT4gICAgPHBhdGggZD0iTTQwLDAgdjQwIGgtNDAgTDE0IDMzIGgxMiB2LTI2IHoiIGZpbGw9IiMzNDNhNDAiIHNoYXBlLXJlbmRlcmluZz0iYXV0byIgc3Ryb2tlLXdpZHRoPSIwIiBzdHJva2U9IiMzNDNhNDAiIHN0cm9rZS1saW5lam9pbj0icm91bmQiLz48L3BhdHRlcm4+PC9kZWZzPiA8cmVjdCBmaWxsPSJ1cmwoI3BhdHRlcm4pIiBoZWlnaHQ9IjEwMCUiIHdpZHRoPSIxMDAlIiB5PSIwIiB4PSIwIi8+PC9zdmc+");
}
</style>
