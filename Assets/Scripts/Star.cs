using UnityEngine;
using System.Collections;

public class Star : MonoBehaviour {
	
	public string SceneName;
	public bool gameFinished;
	
	// Use this for initialization
	void Start () {
		gameFinished = false;
	
	}
	
	// Update is called once per frame
	void Update () {
		if (gameFinished == true){
			if (Input.GetKey(KeyCode.KeypadEnter) || Input.GetKey(KeyCode.Return))
				Application.LoadLevel (SceneName);
		}
	}
	
	void OnTriggerEnter() {
		GameObject	textPivot = GameObject.Find("Text Pivot");
		GameObject	clearedLevelPlane = GameObject.Find("Plane");
		
		
		if (clearedLevelPlane != null)
			clearedLevelPlane.animation.Play();
		if (textPivot != null)
			textPivot.SetActive(false);
		gameFinished = true;
	}
}
