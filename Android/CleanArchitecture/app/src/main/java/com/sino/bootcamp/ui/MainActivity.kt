package com.sino.bootcamp.ui

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.datastore.core.DataStore
import androidx.lifecycle.ViewModelProvider
import com.sino.bootcamp.Global
import com.sino.bootcamp.ui.login.LoginScreen
import com.sino.bootcamp.ui.login.LoginViewModel
import com.sino.bootcamp.ui.theme.BootCampTheme

class MainActivity : ComponentActivity() {
    //lateinit var loginViewModel :LoginViewModel
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Global.context = applicationContext;
        val loginViewModel = ViewModelProvider(this).get(LoginViewModel::class.java)

        setContent {
            BootCampTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    LoginScreen(loginViewModel)
                }
            }
        }
    }
}

