package com.sino.bootcamp.ui.login

import android.annotation.SuppressLint
import androidx.compose.foundation.layout.Column
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember

//UI Element

@SuppressLint("UnrememberedMutableState")
@Composable
fun LoginScreen(viewModel: LoginViewModel) {

    val loginUiState by viewModel.loginUiState.collectAsState()

    Column {
        Button(onClick = { viewModel.onLoginByPhoneSmsCodeTriggered("13811118888","1234")}) {
            Text(text = "Login")
        }

        when(loginUiState){
            LoginUiState.Login -> Text(text = "already Login")
            LoginUiState.UnLogin -> Text(text = "not Login")
        }
    }

}

