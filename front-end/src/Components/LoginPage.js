import axios from 'axios'
import React, { useState } from 'react'
import {Router,Routes,Route,Link,useNavigate} from 'react-router-dom';
import {Form,Button,Row,Col, Card,Alert} from 'react-bootstrap'
import MD5 from "crypto-js/md5";


function LoginPage() {

    const grant_login = () =>{
        const str = `/api/admin/login?admin_id=${username}`
        console.log(str)
        axios.get(`/api/admin/login?admin_id=${username}`)
        .then(res=>{

            // res.data.password_hash===MD5(password).toString();
            console.log( res.data.password_hash)
            setSuc(true);

            if(MD5(password).toString()===res.data.password_hash)
            {
                console.log("user authentiated");
                newhistory("/dashboard")
                b=<Alert variant="success"> <p>User Logged In</p></Alert>
            }
            else{
                b=<Alert variant="Danger"> <p>Wrong ID or Password</p></Alert>
            }

        })
        // .error(err=>{
        //     console.log(err)
        // })
        
    }
    const newhistory = useNavigate();
    const [suc,setSuc] = useState(false)
    const [username,setUsername] = useState("")
    const [password,setPassword] = useState("")
    let b;

  return (
        <div >
            <Row style={{height:"95vh"}}>
                <Col xs={4}></Col>
                <Col xs={4} style={{textAlign:"left"}}>
                <Card style={{padding:"30px",width:"100%",marginTop:"30vh",maxHeight:"17em"}}>
                <Form >
            <Form.Group className="mb-3" controlId="formBasicEmail">
                <Form.Label>Email address</Form.Label>
                <Form.Control value={username} onChange={e=>{setUsername(e.target.value)}} type="text" placeholder="Enter email" />
            </Form.Group>

            <Form.Group className="mb-3" controlId="formBasicPassword">
                <Form.Label>Password</Form.Label>
                <Form.Control value={password} onChange={e=>{setPassword(e.target.value)}} type="password" placeholder="Password" />
            </Form.Group>
            <Button variant="primary" onClick={()=>{
                console.log("clicked");
                grant_login();
            }}>
                Submit
            </Button>
            </Form>
                </Card>
                {suc&&b}

                </Col>
                <Col xs={4}></Col>
            </Row>
            
        </div>
  )
}

export default LoginPage