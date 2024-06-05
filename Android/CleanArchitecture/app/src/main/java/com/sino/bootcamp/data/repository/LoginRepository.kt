package com.sino.bootcamp.data.repository


import kotlinx.coroutines.flow.Flow

interface LoginRepository {
     fun login(phone: String, code: String): String;
}

