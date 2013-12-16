using UnityEngine;
using System.Collections;

public class Panel : MonoBehaviour {
	
	bool clicked;
	float startTime;
	float lastTime;
	float animTime = 0.5f;
	
	// Use this for initialization
	void Start () {
		clicked = false;
	}
	
	// Update is called once per frame
	void Update () {
		if (!clicked && Input.GetMouseButtonDown(0)) {
			Camera camera = GameObject.FindGameObjectWithTag("GUICamera").GetComponent<Camera>();
			
			if (Physics.Raycast(camera.ScreenPointToRay(Input.mousePosition))) {
				clicked = true;
				startTime = Time.time;
				lastTime = Time.time;
				GameObject canon = GameObject.Find("Cannon");
			
				Debug.Log ("Aoutch !");
				canon.SendMessage("ResetAll");				
			}
		}
		if (clicked) {
			float delta = (Time.time - lastTime);
			if (Time.time - startTime > animTime) {
				clicked = false;
				delta = animTime - (lastTime - startTime);
			}
			transform.Rotate(Vector3.up, 360.0f * delta / animTime);
			lastTime = Time.time;
		}
	}
}
