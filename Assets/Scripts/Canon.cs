using UnityEngine;
using System.Collections;

public class Canon : MonoBehaviour {
	
	public float power;
	public float minAngleLeftX;
	public float maxAngleRightX;
	public GameObject ballEmiter;
	public GameObject ball;
	public float angleX;
	
	GameObject nextBall;
	
	// Use this for initialization
	void Start () {
		Quaternion rot=new Quaternion();
       	rot.eulerAngles = new Vector3(0, 0, 0);
       	transform.rotation=rot;
		transform.RotateAround(transform.position, new Vector3(1, 0, 0), angleX);
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKey(KeyCode.RightArrow)) {
			if ( angleX < maxAngleRightX ) {
				transform.RotateAround(transform.position, new Vector3(1, 0, 0), 1f);
				angleX++;
			}
		}
		if (Input.GetKey(KeyCode.LeftArrow)) {
			if ( angleX > minAngleLeftX ) {
				transform.RotateAround(transform.position, new Vector3(1, 0, 0), -1f);
				angleX--;
			}
		}
		if (Input.GetKeyDown(KeyCode.Space)) {
			nextBall = (GameObject) Instantiate(ball, ballEmiter.transform.position, Quaternion.identity);
			Vector3 dir = ballEmiter.transform.position - transform.position;
			dir *= power;
			nextBall.rigidbody.AddForce(dir, ForceMode.Impulse);
		}
	}
}
