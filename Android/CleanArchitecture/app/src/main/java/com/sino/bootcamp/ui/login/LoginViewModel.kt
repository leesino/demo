package com.sino.bootcamp.ui.login

import android.util.Log
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.setValue
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.sino.bootcamp.domain.usecase.LoginUseCase
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch

class LoginViewModel(
    private val loginUseCase: LoginUseCase = LoginUseCase(),
) : ViewModel() {
    private var _loginUiState = MutableStateFlow<LoginUiState>(LoginUiState.UnLogin)
    val loginUiState: StateFlow<LoginUiState> = _loginUiState

    fun onLoginByPhoneSmsCodeTriggered(phone:String, code :String){
        Log.i("LoginViewModel","loginByPhoneSmsCode")
        viewModelScope.launch {
            val result = loginUseCase(phone,code) //how to get result and update loginUiState
            Log.i("LoginViewModel","loginByPhoneSmsCode result = ${result}")

            _loginUiState.emit(LoginUiState.Login)
        }
    }

}