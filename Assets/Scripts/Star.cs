﻿using UnityEngine;
using System.Collections;

public class Star : MonoBehaviour {
	
	public string SceneName;
	
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	void OnTriggerEnter() {
		Application.LoadLevel (SceneName);
	}
}
