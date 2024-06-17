package com.example.compose.ui.theme.sample


import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.text.KeyboardActions
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.AccountBox
import androidx.compose.material.icons.filled.Person
import androidx.compose.material3.Icon
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.input.ImeAction
import androidx.compose.ui.text.input.KeyboardCapitalization
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.PasswordVisualTransformation
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp


@Composable
fun TextFieldSample1() {
    var text by remember { mutableStateOf("Hello") }

    TextField(
        value = text,
        onValueChange = { text = it },
        label = { Text("Label") }
    )
}

@Composable
fun TextFieldSample2() {
    var text by remember { mutableStateOf("Hello") }

    OutlinedTextField(
        value = text,
        onValueChange = { text = it },
        label = { Text("Label") }
    )
}

@Composable
fun TextFieldSample3() {
    var value by remember { mutableStateOf("Hello\nWorld\nInvisible") }

    TextField(
        value = value,
        onValueChange = { value = it },
        label = { Text("Enter text") },
        maxLines = 2,
        textStyle = TextStyle(color = Color.Red,
            fontWeight = FontWeight.Bold),
        modifier = Modifier.padding(20.dp)
    )
}

@Composable
fun TextFieldSample4() {
    var text by remember { mutableStateOf("") }
    val brush = remember {
        Brush.linearGradient(
            colors = listOf(Color.Red,Color.Green,Color.Blue)
        )
    }
    TextField(
        value = text, onValueChange = { text = it },
        textStyle = TextStyle(brush = brush)
    )
}

@Composable
fun TextFieldSample5() {
    var password by rememberSaveable { mutableStateOf("") }

    TextField(
        value = password,
        onValueChange = { password = it },
        label = { Text("Enter password") },
        visualTransformation = PasswordVisualTransformation(),
        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Password)
    )
}

@Composable
fun TextFieldSample6() {
    var text by remember { mutableStateOf("Hello") }
    Column {
        TextField(
            value = text,
            onValueChange = { text = it },
            label = { Text("Label") },
            keyboardOptions = KeyboardOptions(capitalization =
            KeyboardCapitalization.Words)
        )
        TextField(value = text, onValueChange = {text = it},
            keyboardOptions = KeyboardOptions(imeAction = ImeAction.Search)
        )
    }
}

@Composable
fun TextFieldSample7() {
    var text by remember { mutableStateOf("") }
    TextField(
        value = text,
        onValueChange = { text = it },
        label = {Text("label")},
        placeholder = {Text(text = "please input text")},
        leadingIcon = {
            Icon(imageVector = Icons.Default.AccountBox,
                contentDescription = null) },
        trailingIcon = {
            Icon(imageVector = Icons.Default.Person,
                contentDescription = null) },
        keyboardActions = KeyboardActions(onDone = {
        }),
        keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
        singleLine = true,
        maxLines = 1
    )

}

@Preview
@Composable
fun TextFieldSamplePreview() {
    TextFieldSample7()
}
